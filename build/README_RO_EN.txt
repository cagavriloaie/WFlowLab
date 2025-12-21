        ROMANA

*****************************************************
* VĂ RUGĂM SALVAȚI ACEST FIȘIER TEXT ÎNTR-O LOCAȚIE *
* CUNOSCUTĂ PENTRU REFERINȚE VIITOAR                *
*****************************************************

**Istoric**
V 0.9 (02.2023) – Lansare neoficială, în curs de dezvoltare.  
V 1.0 (05.2023) – Prima lansare oficială, cu detectare automată a interfeței RS-485.  
V 1.1 (11.2023) – Corectarea traducerilor și adăugarea restricțiilor la introducerea datelor.  
V 1.2 (01.2024) – Adăugarea unui document PDF pentru raportul metrologic.  
V 1.3 (03.2024) – Corecții pentru fișierul PDF generat pentru FM.  
V 1.4 (07.2024) – Îmbunătățiri ale interfeței utilizator (UI).  
V 1.5 (01.2025) – Adăugarea de observații în formularul „Buletin de Verificare Metrologică” și
                  remedierea limitării  privind numărul maxim de apometre supuse verificării.
V 1.6 (06.2025) – Corecție la calculul factorului de corecție a volumului de apă.
V 1.7 (01.2026) – Metoda corectie volum este configurabila

**Sistem de operare țintă**
   - Windows 11, lansat în 2021 sau ulterior
   - Windows 10, lansat în 2015 sau ulterior

**Arhitectură**
   x86
   > dumpbin WaterStreamLab.exe | findstr machine
     14C machine (x86)
     
**Utilizare**
Asigurați-vă că aveți instalat un cititor PDF (de ex., Adobe Acrobat Reader) pentru
a vizualiza fișele de măsurători.
Doar o instanță a aplicației poate fi lansată la un moment dat.
Setările aplicației sunt salvate automat în Windows Registry.

Exemplu de fișier de licență:
    company=Elcost Company>
    archive=C:/Stand/Fise>
    volume_correction=CLASSIC_VOLUME_CORRECTION>
    certificate=CE 06.02-2025/15>
    density_20=998.2010>
    control=004b3d5b6f320ab986035bf8252ea845>

company - Numele companiei;
archive - Directorul pentru stocarea documentelor PDF;
volume_correction - Metoda folosita pentru corectia volumului:
       >CLASSIC_VOLUME_CORRECTION
       >INM_VOLUME_CORRECTION
       >ELCOST_VOLUME_CORRECTION
certificate - Numărul certificatului pentru instrumentul de măsurare;
density_20 - Densitatea apei la 20°C specifică fiecărui punct de lucru;
control - Suma de control a licenței

Modificarea câmpurilor "company" sau "volume_correction" invalidează licența (consultați manualul aplicației).
Doar Elcost poate modifica acest lucru generând o nouă semnătură digitală.
Citirea automată a indexului necesită conexiuni RS485 sau RS422 către punctele de date.
Aplicația verifica metrologic contoarele de apă utilizând un stand de testare, manual sau prin RS485 sau RS422 cu protocolul MODBUS.

Pentru detalii privind instalarea, dezinstalarea, configurarea și utilizarea, consultați manualul inclus.

**Referinte**
- RS-485: https://en.wikipedia.org/wiki/RS-485
- RS-422: https://en.wikipedia.org/wiki/RS-422
- MODBUS: https://en.wikipedia.org/wiki/MODBUS

**Drepturi și utilizare**
Water Stream Laboratory este un software proprietar dezvoltat de ELCOST Company. Drepturile de utilizare, copiere,
modificare sau distribuire a acestui software sunt guvernate de acordul de licență inclus cu software-ul.

**Contact**
Pentru întrebări referitoare la licențiere și permisiuni de utilizare, vă rugăm să contactați:
    Constantin Agavriloaie
    Email: office@elcost.ro
    Telefon: +40-720.220.588 | +40-729.976.618
    Adresă: RO, IS Pașcani Str. Morilor 8



        ENGLISH

****************************************************
*   PLEASE SAVE THIS TEXT FILE IN A KNOWN LOCATION *
*   FOR FUTURE REFERENCE                           *
****************************************************

** History ** 
V 0.9 (02.2023) – Unofficial release, under development.
V 1.0 (05.2023) – First official release, with automatic detection of the RS-485 interface.
V 1.1 (11.2023) – Translation corrections and added data input restrictions.
V 1.2 (01.2024) – Added PDF generation for the metrological report.
V 1.3 (03.2024) – Fixes for the generated FM PDF file.
V 1.4 (07.2024) – User interface (UI) improvements.
V 1.5 (01.2025) – Added notes to the "Metrological Verification Bulletin" form and fixed the issue
                  limiting the maximum number of water meters for verification.
V 1.6 (06.2025) – Fixed the water volume correction factor calculation.
V 1.7 (01.2026) – The volume correction method is configurable.

**Target OS**
   - Windows 11, released in 2021 or later
   - Windows 10, released in 2015 or later

**Architecture**
   x86
   > dumpbin WaterStreamLab.exe | findstr machine
     14C machine (x86)

**Usage**
Ensure you have a PDF reader (e.g., Adobe Acrobat Reader) installed to view measurement sheets.
Only one instance of the application can be launched at a time.
Application settings are automatically stored in the Windows Registry.

The license file is located at:
    C:\Program Files\Water Stream Laboratory\watermeters.conf

Example license file:
    company=Elcost Company>
    archive=C:/Stand/Fise>
    volume_correction=CLASSIC_VOLUME_CORRECTION>
    certificate=CE 06.02-2025/15>
    density_20=998.2010>
    control=004b3d5b6f320ab986035bf8252ea845>

company – Company name;
archive – Directory for storing PDF documents;
volume_correction – Method used for volume correction:
        > CLASSIC_VOLUME_CORRECTION
        > INM_VOLUME_CORRECTION
        > ELCOST_VOLUME_CORRECTION
certificate – Certificate number for the measuring instrument;
density_20 – Water density at 20 °C, specific to each operating location;
control – License checksum.

Modifying the “company” or “volume_correction” fields invalidates the license (refer to the application manual).
Only Elcost can perform such changes by generating a new digital signature.
Automatic index reading requires RS-485 or RS-422 connections to data points.
The application performs metrological verification of water meters using a test bench, either manually 
or via RS-485 or RS-422 using the MODBUS protocol.

For installation, uninstallation, configuration, and usage details, refer to the included manual.

**References**
- RS-485: https://en.wikipedia.org/wiki/RS-485
- RS-422: https://en.wikipedia.org/wiki/RS-422
- MODBUS: https://en.wikipedia.org/wiki/MODBUS

**Rights and Usage**
Water Stream Laboratory is proprietary software developed by ELCOST Company. Rights to use, copy, modify, or distribute this software are governed by the license agreement included with the product.

**Contact**
For licensing and usage inquiries:
    Constantin Agavriloaie
    Email: office@elcost.ro
    Phone: +40-720.220.588 | +40-729.976.618
    Address: RO, IS Pascani Str. Morilor no. 8
