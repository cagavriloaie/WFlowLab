>>>>>>>>>>>>>>>>> WStreamLab >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

****************************************************
*  PLEASE SAVE THIS TEXT FILE IN A KNOWN LOCATION  *
*  TO BE ABLE TO BE CONSULTED LATER                *
****************************************************

History:
V 0.9  02.2023  Not official release, under development;
V 1.0  05.2023  First official release, automatically interface RS 485 detection;
V 1.1  11.2023  Fixing translations and add restriction for data input;
V 1.2  01.2024  Added metrological report pdf document;
V 1.3  03.2024  Read options configuration file more security;
                Added volume correction coefficient; 

Application can be installed and run under Windows OS with versions:

   Windows 11, released in 2021 or newer
   Windows 10, released in 2015 or newer

Architecture:
   IA-32
   x86-64
   
Recomanded display resolution:
   1920 x 1080 or higher
   
It is good to have an application for reading PDF files installed on your computer (such as Adobe Acrobat Reader) 
to be able to view and read the measurement sheets.

Just an instance of the application can be launch at a moment in time.

Application is based on some configurations that are automatically saved in Windows Registry.

The license must be set generated depending on the configuration of the work point.

Location of license file: 
    C:\Program Files (x86)\WStreamLab\watermeters.conf

Example license file:
    company=EMAX>
    archive=C:/Stand/Fise>
    maximum=20>
    certificate=CE 06.02-355/15>
    density_20=998.2455>
    control=3d15c080f683674e44d3c891d68919db>

> company     - the company name;
> archive     - the folder where are saved and kept all generated PDF documents;
> maximum     - the maximum number of water meters that are tested simultaneously;
> certificate - the certificate number for this measuring instrument; 
> density_20  - the density of water @20°C and is specific to each point of work;
> control     - the control sum generated for this license

Changing the "company" and/or "maximum" fields leads to invalidate the license (see the application manual). 
This can done only by Elcost by generating another digital signature.

The use of the automatic index reading option can only be done when there is a RS485 MODBUS connection
to the data collection points.

To be able to work under appropriate conditions, you should have a PDF file reader 
and a CSV file editor installed on your computer.

More information related to installation, uninstallation, configuration and use of the application 
can be obtained from the manual that is part of this kit.

For any issues regarding the license, please contact:
    Constantin Agavriloaie
    office@elcost.ro
    +40-720.220.588
    +40-729.976.618
    ROMANIA / CJ

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

