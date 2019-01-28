    -----------------------------------------------------------------------------

                   --- CAEN SpA - Computing Systems Division --- 

    -----------------------------------------------------------------------------

    CAENDPP Library Rel. 1.7.2
    
    Installation and Use Instructions

    -----------------------------------------------------------------------------

    Jul 2017

    -----------------------------------------------------------------------------


  
 
 Content 
 -------

  - Library and development files

  
 System Requirements
 -------------------
 
 - CAEN Digitizer board with supported DPP-PHA firmware or CAEN MCA board
 - Windows 7/8/8.1/10 or Linux with kernel >= 2.4
 - For Windows systems:
    - Visual Studio 2010 or later
 - For Linux systems:
    - gnuplot-x11 package
    - C compilation environment

 Installation notes
 ------------------
 
 WINDOWS:
    - Run the CAENDPPLibSetup.exe setup program.
    - To Run the DemoDPPLib: copy 'DemoDPPLib' folder from installation
      directory to a User-writable location (if needed) and open the VS2010
      solution located in 'build' directory.
 
 LINUX:
    - Extract the archive
    - Execute the installation script 'install' from the extracted directory
    - To Run the DemoDPPLib: copy 'DemoDPPLib' folder from installation
      directory to a User-writable location (if needed) and run:
      $ make
      # make install # as root
    