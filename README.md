# Speuren met Krul (2021)

C++ console application created in 2021 as part of a school assignment by **Ferran Hendriks (2130858)**.  
The project is built with **Visual Studio** and uses **libcurl** for HTTP/HTTPS requests.

> ⚠️ This repository is primarily configured and tested for **Windows** with **Visual Studio 2019** and **x86 (Win32)** builds.

---

## Project Goals

- Provide a small C++ console project for the *Speuren met Krul* assignment.
- Demonstrate how to:
  - Set up a Visual Studio C++ project.
  - Link against **libcurl** as a static library.
  - Use curl from C++ code (HTTP/HTTPS requests, etc.).

If you’re looking at this repo as part of a portfolio:  
it mainly showcases **C++**, **Visual Studio tooling**, and **native library integration** (libcurl).

---

## Tech Stack

- **Language:** C++  
- **IDE:** Visual Studio 2019 (v142 toolset)  
- **Platform:** Windows, **Win32 (x86)** and x64 configurations available  
- **Networking library:** [libcurl](https://curl.se/libcurl/) (linked statically)  

---

## Repository Structure

```text
Speuren-met-Krul-2021/
├─ src/                         # All C++ source files (program logic)
├─ Speuren-metKrul-2.sln       # Visual Studio solution
├─ Speuren-metKrul-2.vcxproj   # Visual Studio project file
├─ Speuren-metKrul-2.vcxproj.filters
├─ .gitignore
├─ .gitattributes
└─ README.md                    # This file
