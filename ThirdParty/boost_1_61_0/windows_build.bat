#REM "build all - MT/MTd (32bit Lib)"
#b2 --prefix=.\stage\lib --toolset=msvc-14.0  runtime-link=static

#REM "build all -  MD/MDd(32bit DLL)"
#b2 --prefix=.\stage\lib --toolset=msvc-14.0  runtime-link=shared

#REM "build all - MT/MTd (64bit Lib)"
#b2 --prefix=.\stage\lib64 --toolset=msvc-14.0  runtime-link=static --architecture=x64 address-model=64

#REM "build all - MD/MDd(64bit DLL)"
#b2 --prefix=.\stage\lib64 --toolset=msvc-14.0  runtime-link=shared --architecture=x64 address-model=64