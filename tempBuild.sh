rm -f PrismCoordinates.txt
rm -f RayCoordinates.txt
g++ Source.cpp opticalMedia.cpp  geometricUtils.cpp light.cpp opticalFormulae.cpp  -o a.exe
./a.exe
rm -f a.exe
python3 ./plotSimulation.py
