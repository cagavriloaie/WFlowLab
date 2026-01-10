        ROMANA

*****************************************************
* VĂ RUGĂM SALVAȚI ACEST FIȘIER TEXT ÎNTR-O LOCAȚIE *
* CUNOSCUTĂ PENTRU REFERINȚE VIITOARE               *
*****************************************************

**Despre WStreamLab**
WStreamLab (Water Stream Laboratory) este o aplicație profesională pentru verificarea metrologică
a contoarelor de apă. Aplicația oferă suport complet pentru metode volumetrice și gravimetrice,
generează rapoarte PDF detaliate și asigură conformitatea cu standardele metrologice internaționale.

**Caracteristici principale**
   • Verificare metrologică pentru până la 20 apometre simultan
   • Metode de măsurare: volumetrică și gravimetrică
   • Generare automată de rapoarte PDF cu buletin de verificare metrologică
   • Trei nivele de debit: Q1 (minim), Q2 (tranzitoriu), Q3 (nominal)
   • Calcul automat al erorilor de măsurare
   • Corecție a volumului de apă în funcție de temperatură și densitate
   • Suport multi-lingv (Română / English)
   • Bază de date extensibila cu tipuri de apometre
   • Salvare și încărcare date de măsurare
   • Interfață intuitivă cu validare în timp real

**Istoric**
V 0.9 (02.2023) – Lansare neoficială, în curs de dezvoltare.
V 1.0 (05.2023) – Prima lansare oficială, cu detectare automată a interfeței RS-485.
V 1.1 (11.2023) – Corectarea traducerilor și adăugarea restricțiilor la introducerea datelor.
V 1.2 (01.2024) – Adăugarea unui document PDF pentru raportul metrologic.
V 1.3 (03.2024) – Corecții pentru fișierul PDF generat pentru raportul metrologic.
V 1.4 (07.2024) – Îmbunătățiri ale interfeței utilizator (UI).
V 1.5 (01.2025) – Adăugarea de observații în formularul „Buletin de Verificare Metrologică"
                  și remedierea limitării privind numărul maxim de apometre supuse verificării.
V 1.6 (06.2025) – Corecție la calculul factorului de corecție a volumului de apă.
V 1.7 (12.2025) – Metoda de corecție a volumului este configurabilă.
V 1.8 (01.2026) – Îmbunătățiri UI și adăugarea documentației metodei de verificare
                  în meniul Ajutor (Help → Metoda de Verificare / Verification Method),
                  cu suport multi-lingv și afișare HTML. Corectare bug-uri la salvarea
                  și încărcarea datelor de măsurare.

**Cerințe de sistem**
   Sistem de operare:
      - Windows 11 (2021 sau ulterior) - recomandat
      - Windows 10 (2015 sau ulterior)

   Hardware minim:
      - Procesor: Intel/AMD x86 compatibil, 1 GHz sau mai rapid
      - Memorie RAM: 2 GB (4 GB recomandat)
      - Spațiu pe disc: 50 MB pentru aplicație + spațiu pentru rapoarte PDF
      - Rezoluție ecran: 1280x720 sau mai mare (1920x1080 recomandat)

   Software necesar:
      - Cititor PDF (Adobe Acrobat Reader, Foxit Reader, sau similar)
      - .NET Framework (inclus automat în Windows 10/11)

**Arhitectură**
   x86 (32-bit)
   > dumpbin WStreamLab.exe | findstr machine
     14C machine (x86)

**Instalare**
   1. Rulați fișierul de instalare WStreamLab_Setup.exe
   2. Urmați instrucțiunile asistentului de instalare
   3. Acceptați acordul de licență
   4. Aplicația va crea automat directoarele necesare pentru:
      - Fișiere de configurare
      - Rapoarte PDF generate
      - Date de măsurare salvate

**Pornire rapidă**
   1. Lansați aplicația din meniul Start sau de pe Desktop
   2. La prima pornire, configurați:
      - Limba dorită (RO/EN)
      - Tipul de apometru
      - Numărul de apometre de verificat
      - Condițiile de laborator (temperatură, presiune, umiditate)
   3. Selectați metoda de măsurare (Volumetrică sau Gravimetrică)
   4. Introduceți datele de măsurare în tabelul principal
   5. Apăsați "Calculate" pentru calculul automat al erorilor
   6. Generați fișa măsurători PDF prin "Generare FM"
   7. Generați buletin verificare metrologică PDF prin "Generare BV"

**Utilizare**
Asigurați-vă că aveți instalat un cititor PDF (de ex., Adobe Acrobat Reader) pentru
a vizualiza fișele de măsurători.

Doar o instanță a aplicației poate fi lansată la un moment dat. Dacă încercați să lansați
o a doua instanță, veți fi redirecționat automat către fereastra deschisă.

Setările aplicației sunt salvate automat în Windows Registry la:
   HKEY_CURRENT_USER\Software\ELCOST\WStreamLab

Fișierul de licență se află la:
   C:\Program Files (x86)\WStreamLab\watermeters.conf

Exemplu de fișier de licență:
    company=Elcost Company>
    archive=C:/Stand/Fise>
    volume_correction=CLASSIC_VOLUME_CORRECTION>
    certificate=CE 06.02-2025/15>
    density_20=998.2010>
    control=004b3d5b6f320ab986035bf8252ea845>

Parametrii fișierului de licență:
   company – Numele companiei autorizate;
   archive – Directorul pentru stocarea documentelor PDF generate;
   volume_correction – Metoda folosită pentru corecția volumului:
         > CLASSIC_VOLUME_CORRECTION - Metoda clasică standard
         > INM_VOLUME_CORRECTION - Metoda Institutului Național de Metrologie
         > ELCOST_VOLUME_CORRECTION - Metoda proprietară ELCOST
   certificate – Numărul certificatului pentru instrumentul de măsurare;
   density_20 – Densitatea apei la 20°C specifică fiecărui punct de lucru;
   control – Suma de control MD5 a licenței (semnătură digitală)

IMPORTANT: Modificarea câmpurilor "company" sau "volume_correction" invalidează licența
(consultați manualul aplicației). Doar Elcost poate modifica aceste valori generând
o nouă semnătură digitală.

**Rezolvarea problemelor**
   Problemă: Aplicația nu pornește
      → Verificați dacă aveți Windows 10/11 actualizat
      → Reinstalați aplicația
      → Contactați suportul tehnic

   Problemă: Nu se pot salva rapoarte PDF
      → Verificați permisiunile pentru directorul "archive" din fișierul de licență
      → Asigurați-vă că aveți spațiu suficient pe disc
      → Verificați că aveți un cititor PDF instalat

   Problemă: Eroare de licență invalidă
      → NU modificați manual fișierul watermeters.conf
      → Contactați ELCOST pentru o licență validă

   Problemă: Datele introduse dispar la redeschiderea dialogului
      → Salvați datele folosind butonul "Save Current Input Data"
      → Încărcați datele salvate cu "Open Input Data"

**Actualizări și suport**
   Pentru actualizări și asistență tehnică, vizitați:
      Website: www.elcost.ro
      Email: office@elcost.ro

   Actualizările aplicației pot fi instalate peste versiunea existentă fără a pierde
   configurațiile și datele salvate.

**Drepturi și utilizare**
Water Stream Laboratory este un software proprietar dezvoltat de ELCOST Company.
Drepturile de utilizare, copiere, modificare sau distribuire a acestui software
sunt guvernate de acordul de licență inclus cu software-ul.

Acest software este protejat de legile drepturilor de autor și tratatele internaționale.
Reproducerea sau distribuirea neautorizată a acestui program sau a oricărei părți
din acesta poate duce la sancțiuni civile și penale severe.

**Contact**
Pentru întrebări referitoare la licențiere, suport tehnic și permisiuni de utilizare:
    ELCOST Company
    Reprezentant: Constantin Agavriloaie
    Email: office@elcost.ro
    Telefon: +40-720.220.588 | +40-729.976.618
    Adresă: România, Iași, Pașcani, Str. Morilor nr. 8
    Website: www.elcost.ro



        ENGLISH

****************************************************
*   PLEASE SAVE THIS TEXT FILE IN A KNOWN LOCATION *
*   FOR FUTURE REFERENCE                           *
****************************************************

**About WStreamLab**
WStreamLab (Water Stream Laboratory) is a professional application for metrological verification
of water meters. The application provides complete support for volumetric and gravimetric methods,
generates detailed PDF reports, and ensures compliance with international metrological standards.

**Main Features**
   • Metrological verification for up to 20 water meters simultaneously
   • Measurement methods: volumetric and gravimetric
   • Automatic PDF report generation with metrological verification bulletin
   • Three flow rate levels: Q1 (minimum), Q2 (transitional), Q3 (nominal)
   • Automatic measurement error calculation
   • Water volume correction based on temperature and density
   • Multi-language support (Romanian / English)
   • Extensive database of water meter types
   • Save and load measurement data
   • Intuitive interface with real-time validation

**History**
V 0.9 (02.2023) – Unofficial release, under development.
V 1.0 (05.2023) – First official release, with automatic RS-485 interface detection.
V 1.1 (11.2023) – Translation corrections and addition of data input restrictions.
V 1.2 (01.2024) – Addition of a PDF document for the metrological report.
V 1.3 (03.2024) – Corrections for the generated PDF file for the metrological report.
V 1.4 (07.2024) – User interface (UI) improvements.
V 1.5 (01.2025) – Addition of observations in the "Metrological Verification Bulletin" form and fixing
                  the limitation regarding the maximum number of water meters under verification.
V 1.6 (06.2025) – Correction to the water volume correction factor calculation.
V 1.7 (12.2025) – Volume correction method is configurable.
V 1.8 (01.2026) – UI improvements and addition of verification method documentation in the Help menu
                  (Help → Verification Method), with multi-language support and HTML display.
                  Bug fixes for saving and loading measurement data.

**System Requirements**
   Operating System:
      - Windows 11 (2021 or later) - recommended
      - Windows 10 (2015 or later)

   Minimum Hardware:
      - Processor: Intel/AMD x86 compatible, 1 GHz or faster
      - RAM: 2 GB (4 GB recommended)
      - Disk Space: 50 MB for application + space for PDF reports
      - Screen Resolution: 1280x720 or higher (1920x1080 recommended)

   Required Software:
      - PDF reader (Adobe Acrobat Reader, Foxit Reader, or similar)
      - .NET Framework (automatically included in Windows 10/11)

**Architecture**
   x86 (32-bit)
   > dumpbin WStreamLab.exe | findstr machine
     14C machine (x86)

**Installation**
   1. Run the installation file WStreamLab_Setup.exe
   2. Follow the installation wizard instructions
   3. Accept the license agreement
   4. The application will automatically create necessary directories for:
      - Configuration files
      - Generated PDF reports
      - Saved measurement data

**Quick Start**
   1. Launch the application from Start menu or Desktop
   2. On first launch, configure:
      - Desired language (RO/EN)
      - Water meter type
      - Number of water meters to verify
      - Laboratory conditions (temperature, pressure, humidity)
   3. Select measurement method (Volumetric or Gravimetric)
   4. Enter measurement data in the main table
   5. Press "Calculate" for automatic error calculation
   6. Generate measurement sheet PDF via "Generate FM"
   7. Generate metrological verification bulletin PDF via "Generate BV"

**Usage**
Ensure you have a PDF reader (e.g., Adobe Acrobat Reader) installed to view measurement sheets.

Only one instance of the application can be launched at a time. If you try to launch a second
instance, you will be automatically redirected to the open window.

Application settings are automatically stored in the Windows Registry at:
   HKEY_CURRENT_USER\Software\ELCOST\WStreamLab

The license file is located at:
   C:\Program Files (x86)\WStreamLab\watermeters.conf

Example license file:
    company=Elcost Company>
    archive=C:/Stand/Fise>
    volume_correction=CLASSIC_VOLUME_CORRECTION>
    certificate=CE 06.02-2025/15>
    density_20=998.2010>
    control=004b3d5b6f320ab986035bf8252ea845>

License file parameters:
   company – Authorized company name;
   archive – Directory for storing generated PDF documents;
   volume_correction – Method used for volume correction:
         > CLASSIC_VOLUME_CORRECTION - Standard classic method
         > INM_VOLUME_CORRECTION - National Institute of Metrology method
         > ELCOST_VOLUME_CORRECTION - ELCOST proprietary method
   certificate – Certificate number for the measuring instrument;
   density_20 – Water density at 20°C, specific to each operating location;
   control – MD5 license checksum (digital signature)

IMPORTANT: Modifying the "company" or "volume_correction" fields invalidates the license
(refer to the application manual). Only Elcost can modify these values by generating
a new digital signature.

**Troubleshooting**
   Problem: Application won't start
      → Check if you have Windows 10/11 updated
      → Reinstall the application
      → Contact technical support

   Problem: Cannot save PDF reports
      → Check permissions for the "archive" directory in the license file
      → Ensure you have sufficient disk space
      → Verify that you have a PDF reader installed

   Problem: Invalid license error
      → DO NOT manually modify the watermeters.conf file
      → Contact ELCOST for a valid license

   Problem: Entered data disappears when reopening the dialog
      → Save data using the "Save Current Input Data" button
      → Load saved data with "Open Input Data"

**Updates and Support**
   For updates and technical assistance, visit:
      Website: www.elcost.ro
      Email: office@elcost.ro

   Application updates can be installed over the existing version without losing
   configurations and saved data.

**Rights and Usage**
Water Stream Laboratory is proprietary software developed by ELCOST Company.
Rights to use, copy, modify, or distribute this software are governed by the
license agreement included with the product.

This software is protected by copyright laws and international treaties.
Unauthorized reproduction or distribution of this program, or any portion
of it, may result in severe civil and criminal penalties.

**Contact**
For licensing inquiries, technical support, and usage permissions:
    ELCOST Company
    Representative: Constantin Agavriloaie
    Email: office@elcost.ro
    Phone: +40-720.220.588 | +40-729.976.618
    Address: Romania, Iasi, Pascani, Str. Morilor no. 8
    Website: www.elcost.ro
