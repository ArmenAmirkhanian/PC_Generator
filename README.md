# PC_Generator
Takes in raw CEMHYD3D microstructures and converts them to a 3D file format that can easily be opened by CloudCompare. This was origninally done in MATLAB but was deemed to be way too slow.

Every effort has been made to optimize the point generator so that it can handle >80 million point files with relative ease. Note that this code utilizes the Boost libraries since it is developed in VS2013 and mman.h is not natively available.
