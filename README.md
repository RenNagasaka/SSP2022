# BRIL generating dummy histogram

This code is generating dummy data macthing BRIL histogram format. For now, the dummy data includes appropriate header, random or single bin counter payload. In this code, we uses "https://gitlab.cern.ch/bril-phase2/bril_histogram.git" as submodule.

# Table of contents
[[_TOC_]]

## Folder Structure
```bash
|-- bril_histogram - ```submodule is contained here```
`-- software- ```C++ library to generate dummy data```
    |-- lib -```output file is delivered here```
    `-- src -```C++ code is here```
```

## How to compile
The generating dummy data module is implemented in C++ and placed in ```your_project_folder/SSP2022/software/```.It is represented by a class called DummyHistogramGenerator which generate dummy histogram in std::vector<uint32_t>.

- Go to the software folder
  > `your_project_folder/SSP2022/software`
- Compile 
  > `make DummyHistogramGenerator`

There is also test.cpp for checking dummy data format is macthing with BrilHistogram class.

- Go to the software folder
  > `your_project_folder/SSP2022/software`
- Compile 
  > `make test`

## How to run test.cpp
When you want to see the output of test.cpp, 

- Go to the lib folder
  > `your_project_folder/SSP2022/software/lib`
- Run
  > `./test.out`

You can see some header values and this means dummy data foramt matching with BrilHistogram class.  
