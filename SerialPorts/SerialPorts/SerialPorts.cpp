#include "pch.h"
#include "SerialPorts.h"
#include <Windows.h>
#include <wbemcli.h>
#include <comdef.h>
#include <boost/lexical_cast.hpp>
#include <string>

# pragma comment(lib, "wbemuuid.lib")

std::wstring result;

const wchar_t* enumerateSerialPorts()
{
    std::map<int, std::wstring> mapSerials;

    HRESULT hres;

    hres = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(hres) || hres == RPC_E_CHANGED_MODE) {
        hres = CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities
            NULL                         // Reserved
        );

        if (SUCCEEDED(hres) || hres == RPC_E_TOO_LATE) {
            IWbemLocator* pLoc = NULL;

            hres = CoCreateInstance(
                CLSID_WbemLocator,
                0,
                CLSCTX_INPROC_SERVER,
                IID_IWbemLocator, (LPVOID*)&pLoc);

            if (SUCCEEDED(hres)) {
                IWbemServices* pSvc = NULL;

                // Connect to the root\cimv2 namespace with
                // the current user and obtain pointer pSvc
                // to make IWbemServices calls.
                hres = pLoc->ConnectServer(
                    bstr_t(L"ROOT\\CIMV2"),  // Object path of WMI namespace
                    NULL,                    // User name. NULL = current user
                    NULL,                    // User password. NULL = current
                    0,                       // Locale. NULL indicates current
                    NULL,                    // Security flags.
                    0,                       // Authority (for example, Kerberos)
                    0,                       // Context object
                    &pSvc                    // pointer to IWbemServices proxy
                );
                if (SUCCEEDED(hres)) {
                    hres = CoSetProxyBlanket(
                        pSvc,                        // Indicates the proxy to set
                        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
                        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
                        NULL,                        // Server principal name
                        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
                        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
                        NULL,                        // client identity
                        EOAC_NONE                    // proxy capabilities
                    );
                    if (SUCCEEDED(hres)) {
                        // Use Win32_PnPEntity to find actual serial ports and USB-SerialPort devices
                        // This is done first, because it also finds some com0com devices, but names are worse
                        IEnumWbemClassObject* pEnumerator = NULL;
                        hres = pSvc->ExecQuery(
                            bstr_t(L"WQL"),
                            bstr_t(L"SELECT Name FROM Win32_PnPEntity WHERE Name LIKE '%(COM%'"),
                            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                            NULL,
                            &pEnumerator);

                        if (SUCCEEDED(hres)) {
                            constexpr size_t max_ports = 30;
                            IWbemClassObject* pclsObj[max_ports] = {};
                            ULONG uReturn = 0;

                            do {
                                hres = pEnumerator->Next(WBEM_INFINITE, max_ports, pclsObj, &uReturn);
                                if (SUCCEEDED(hres)) {
                                    for (ULONG jj = 0; jj < uReturn; jj++) {
                                        VARIANT vtProp;
                                        pclsObj[jj]->Get(L"Name", 0, &vtProp, 0, 0);

                                        // Name should be for example "Serial Port for Barcode Scanner (COM13)"
                                        const std::wstring deviceName = vtProp.bstrVal;
                                        const std::wstring prefix = L"(COM";
                                        size_t ind = deviceName.find(prefix);
                                        if (ind != std::wstring::npos) {
                                            std::wstring nbr;
                                            for (size_t i = ind + prefix.length();
                                                i < deviceName.length() && isdigit(deviceName[i]); i++)
                                            {
                                                nbr += deviceName[i];
                                            }
                                            try {
                                                const int portNumber = boost::lexical_cast<int>(nbr);
                                                mapSerials[portNumber] = deviceName;
                                            }
                                            catch (...) {}
                                        }
                                        VariantClear(&vtProp);

                                        pclsObj[jj]->Release();
                                    }
                                }
                            } while (hres == WBEM_S_NO_ERROR);
                            pEnumerator->Release();
                        }

                        // Use Win32_SerialPort to find physical ports and com0com virtual ports
                        // This is more reliable, because address doesn't have to be parsed from the name
                        pEnumerator = NULL;
                        hres = pSvc->ExecQuery(
                            bstr_t(L"WQL"),
                            bstr_t(L"SELECT DeviceID, Name FROM Win32_SerialPort"),
                            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                            NULL,
                            &pEnumerator);

                        if (SUCCEEDED(hres)) {
                            constexpr size_t max_ports = 30;
                            IWbemClassObject* pclsObj[max_ports] = {};
                            ULONG uReturn = 0;

                            do {
                                hres = pEnumerator->Next(WBEM_INFINITE, max_ports, pclsObj, &uReturn);
                                if (SUCCEEDED(hres)) {
                                    for (ULONG jj = 0; jj < uReturn; jj++) {
                                        VARIANT vtProp1, vtProp2;
                                        pclsObj[jj]->Get(L"DeviceID", 0, &vtProp1, 0, 0);
                                        pclsObj[jj]->Get(L"Name", 0, &vtProp2, 0, 0);

                                        const std::wstring deviceID = vtProp1.bstrVal;
                                        if (deviceID.substr(0, 3) == L"COM") {
                                            const int portNumber = boost::lexical_cast<int>(deviceID.substr(3));
                                            const std::wstring deviceName = vtProp2.bstrVal;
                                            mapSerials[portNumber] = deviceName;
                                        }
                                        VariantClear(&vtProp1);
                                        VariantClear(&vtProp2);

                                        pclsObj[jj]->Release();
                                    }
                                }
                            } while (hres == WBEM_S_NO_ERROR);
                            pEnumerator->Release();
                        }
                    }
                    pSvc->Release();
                }
                pLoc->Release();
            }
        }
        CoUninitialize();
    }
    if (FAILED(hres)) {
        std::stringstream ss;
        ss << "Enumerating serial ports failed. Error code: " << int(hres);
        throw std::runtime_error(ss.str());
    }

    result.clear();

    for (auto port : mapSerials) {
        std::string s("|");
        std::wstring ws;
        ws.assign(s.begin(), s.end());
        result += std::to_wstring(port.first) + ws + port.second + ws;
    }

    return _wcsdup(result.c_str());
}

int main()
{
    const wchar_t* serials = enumerateSerialPorts();
}