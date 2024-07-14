****************************************************
*   PLEASE SAVE THIS TEXT FILE IN A KNOWN LOCATION *
*   FOR FUTURE REFERENCE                           *
****************************************************

**History**
V 0.9   02.2023   Unofficial release, under development;
V 1.0   05.2023   First official release, automatic RS 485 interface detection
V 1.1   11.2023   Fixed translations and added data input restrictions
V 1.2   01.2024   Added metrological report PDF document
V 1.3   03.2024   Supports two MODBUS interfaces

**Target OS**
   - Windows 11, released in 2021 or later
   - Windows 10, released in 2015 or later

**Architecture**
   x86-64
   > dumpbin WaterStreamLab.exe | findstr machine
     8664 machine (x64)

**Usage**
Ensure you have a PDF reader (e.g., Adobe Acrobat Reader) installed to view measurement sheets.
Only one instance of the application can be launched at a time.
Application settings are automatically saved in the Windows Registry.

The license file is located at:
    C:\Program Files\Water Stream Laboratory\watermeters.conf

Example license file:
    company=CUP Focsani>
    archive=C:/Stand/Fise>
    maximum=10>
    certificate=CE 06.02-355/15>
    density_20=998.2009>

> company     - Company name;
> archive     - Directory for storing PDF documents;
> maximum     - Maximum number of water meters that can be tested simultaneously;
> certificate - Certificate number for the measuring instrument;
> density_20  - Water density @20°C specific to each work point;
> control     - License checksum

Altering "company" or "maximum" fields invalidates the license (refer to the application manual).
Only Elcost can modify this by generating a new digital signature.
Automatic index reading requires RS485 or RS422 connections to data points. Learn more about RS485
and RS422 protocols:
The application calibrates water meters using a test bench, manually or via RS485 or RS422 with
MODBUS protocol.

For installation, uninstallation, configuration, and usage details, consult the included manual.

**References**
- RS-485: https://en.wikipedia.org/wiki/RS-485
- RS-422: https://en.wikipedia.org/wiki/RS-422
- MODBUS: https://en.wikipedia.org/wiki/MODBUS

**Rights and Usage**
Water Stream Laboratory 1.3 is proprietary software developed by ELCOST. The rights
to use, copy, modify, or distribute this software are governed by the license agreement included
with the software. Unauthorized reproduction or distribution of this software, or any portion of
it, may result in severe civil and criminal penalties, and will be prosecuted to the maximum extent
possible under the law.

**Contact**
For inquiries regarding licensing and usage permissions, please contact:
    Constantin Agavriloaie
    Email: office@elcost.ro
    Phone: +40-720.220.588 | +40-729.976.618
    Address: RO, IS Pascani Str. Morilor 8 / CJ Cluj-Napoca Str. Constantin Noica 10
