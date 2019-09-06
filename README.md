# GEOSpectralSimulator

GEOSpectralSimulator is a project developed for the 'Universidad Autonoma de Barcelona' as a final grade project. The project is has the finality of provided a multiple tools to download geospatial data (Heights, multispectral textures, etc), transform geospatial data in 3D data, represent the 3D data in a 3D engine like as can be Unreal Engine and extract new data to generate datasets.

<p align="center">
  ![](Video1TFGCortes.gif)
</p>

## Modules developed
- [GEOTool](./GEOTool) - Software in python to download and transform in 3D data.
- [GEOSimulator](./Unreal/GEOSimulator/) - Implementation of a navigator in Unreal Engine.
- [GEOControl](./GEOControl) - Script in python to control a vehicle into Unreal Engine. This also requests images to generate a dataset.
