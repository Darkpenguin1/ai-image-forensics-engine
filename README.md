# AI Image Forensics Engine

A high-performance image forensics and AI-image detection engine built with C++, OpenCV, and OpenMP.

The goal of this project is to analyze images using classical computer vision and statistical image-processing techniques to identify characteristics commonly associated with AI-generated imagery.

This project focuses on:
- Parallel image processing
- Image forensics
- Performance benchmarking
- OpenMP optimization
- Computer vision feature extraction

---

# Features

## Current Goals
- Load and process images using OpenCV
- Extract image statistics and forensic features
- Parallelize image analysis using OpenMP
- Benchmark sequential vs parallel performance

## Planned Detection Methods
- Edge and gradient analysis
- Noise variance analysis
- Texture analysis (LBP)
- Frequency-domain analysis (DCT / FFT)
- Entropy and histogram analysis
- Compression artifact detection

---

# Tech Stack

- C++
- OpenCV
- OpenMP
- CMake

Optional future additions:
- CUDA
- FastAPI
- Python bindings
- Web frontend

---

# Project Motivation

Modern AI-generated images often contain subtle statistical and structural inconsistencies that differ from authentic camera-captured photographs.

This project explores how classical computer vision and parallel computing techniques can be used to:
- Analyze image characteristics
- Detect synthetic artifacts
- Benchmark high-performance image processing workloads

The focus is not solely ML classification accuracy, but building an efficient and scalable image-analysis engine.

---

# Example Analysis Pipeline

Input Image
    ->
Feature Extraction
    ->
Parallel Statistical Analysis
    ->
Weighted Scoring System
    ->
AI Likelihood Output

Example extracted features:
- Edge density
- Noise distribution
- Texture entropy
- Frequency spectrum energy
- Sharpness consistency

---

# Performance Goals

- Compare sequential vs OpenMP execution
- Measure scaling across image sizes
- Explore cache locality and workload partitioning
- Potential CUDA acceleration later

---

# Future Work

- Add machine learning classifier
- Add GPU acceleration with CUDA
- Add REST API with FastAPI
- Add web dashboard for visualization
- Create dataset benchmarking suite

---

# Build

```bash
mkdir build
cd build
cmake ..
make
./forensics_engine