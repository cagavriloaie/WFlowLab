# PowerShell Script to Clean Up Old Registry Keys for WStreamLab
# This script removes old registry keys that have been renamed
# Run this with Administrator privileges if needed

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "WStreamLab Registry Cleanup Tool" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$registryPath = "HKCU:\SOFTWARE\WStreamLab"

# Check if the main registry path exists
if (!(Test-Path $registryPath)) {
    Write-Host "Registry path not found: $registryPath" -ForegroundColor Yellow
    Write-Host "No cleanup needed - registry is clean or doesn't exist yet." -ForegroundColor Green
    exit 0
}

$keysDeleted = 0
$keysNotFound = 0

# Function to delete a registry value if it exists
function Remove-RegistryValue {
    param (
        [string]$Path,
        [string]$Name
    )

    if (Test-Path $Path) {
        $property = Get-ItemProperty -Path $Path -Name $Name -ErrorAction SilentlyContinue
        if ($property) {
            try {
                Remove-ItemProperty -Path $Path -Name $Name -Force
                Write-Host "  [DELETED] $Name" -ForegroundColor Green
                return $true
            }
            catch {
                Write-Host "  [ERROR] Failed to delete $Name : $_" -ForegroundColor Red
                return $false
            }
        }
        else {
            Write-Host "  [SKIP] $Name (not found)" -ForegroundColor Gray
            return $null
        }
    }
    else {
        Write-Host "  [SKIP] Path not found: $Path" -ForegroundColor Gray
        return $null
    }
}

# LabConditions group
Write-Host "`nCleaning up LabConditions group..." -ForegroundColor Yellow
$labPath = "$registryPath\LabConditions"
$result = Remove-RegistryValue -Path $labPath -Name "labTemperature"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $labPath -Name "labHumidity"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $labPath -Name "labPressure"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

# BenchConfiguration group
Write-Host "`nCleaning up BenchConfiguration group..." -ForegroundColor Yellow
$benchPath = "$registryPath\BenchConfiguration"
$result = Remove-RegistryValue -Path $benchPath -Name "typeWaterMeters"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

# Report group
Write-Host "`nCleaning up Report group..." -ForegroundColor Yellow
$reportPath = "$registryPath\Report"
$result = Remove-RegistryValue -Path $reportPath -Name "autorizatiaNumarul"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "numarInregistrare"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "beneficiar"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "codulDinLt"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "normativ"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "valabilitate"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "verificatorMetrolog"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $reportPath -Name "loculEfectuariiVerificarii"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

# RS_485_422 group
Write-Host "`nCleaning up RS_485_422 group..." -ForegroundColor Yellow
$rsPath = "$registryPath\RS_485_422"
$result = Remove-RegistryValue -Path $rsPath -Name "selectedSerial_1"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $rsPath -Name "selectedSerial_2"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $rsPath -Name "retriesNumber_1"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

$result = Remove-RegistryValue -Path $rsPath -Name "retriesNumber_2"
if ($result -eq $true) { $keysDeleted++ } elseif ($result -eq $null) { $keysNotFound++ }

# Summary
Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "Cleanup Summary:" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Keys deleted: $keysDeleted" -ForegroundColor Green
Write-Host "Keys not found (already cleaned/new install): $keysNotFound" -ForegroundColor Gray
Write-Host "`nRegistry cleanup completed successfully!" -ForegroundColor Green
Write-Host ""
