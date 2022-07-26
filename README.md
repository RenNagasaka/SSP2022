# BRIL generating dummy histogram

This code is generating dummy data macthing BRIL histogram format. For now, the dummy data includes appropriate header, random or single bin counter payload. In this code, we uses "https://gitlab.cern.ch/bril-phase2/bril_histogram.git" as submodule.

# Table of contents
[[_TOC_]]

## Folder Structure
|-- bril_histogram - ```submodule is contained here```
|-- lib - ```output files are delivered here```
|--``````
|       `-- firmware
|           |-- ucf - ```timing constraints for the BrilHistogram IP```
|           |-- sim - ```core functionality simulation```
|           |-- hdl - ```IP HDL code```
|           `-- cfg - ```IPbus Builder dependency files```
|   `-- injector - ```injector code that implements testbench
	|-- software - ```python scripts used to test the functionality of the module```
        `-- firmware - ```testbench firmware code```
`-- boards - ```code for various platforms```
    `-- fc7 - ```fc7 based testbench```
    `-- aldec_hes - ```aldec_hes based testbench```        


## How to compile


## How to run
