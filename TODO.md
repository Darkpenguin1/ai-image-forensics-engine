
# TODO.md

```md
# TODO

# Phase 1 - Setup
- [X] Create C++ project structure
- [X] Install and configure OpenCV
- [ ] Configure OpenMP
- [X] Create CMakeLists.txt
- [X] Load image successfully with OpenCV
- [X] Display image info (width, height, channels)

---

# Phase 2 - Basic Image Analysis
- [X] Compute average RGB values
- [X] Convert image to grayscale
- [X] Compute image histogram
- [X] Compute brightness statistics
- [X] Compute entropy

---

# Phase 3 - Edge & Gradient Analysis
- [X] Implement Sobel filter
- [X] Implement Laplacian filter
- [ ] Implement Canny edge detection
- [X] Measure edge density
- [X] Measure image sharpness

---

# Phase 4 - Noise Analysis
- [ ] Compute local variance
- [ ] Analyze noise consistency
- [ ] Compare block-level noise patterns
- [ ] Detect oversmoothed regions

---

# Phase 5 - Texture Analysis
- [ ] Implement Local Binary Patterns (LBP)
- [ ] Compute texture histograms
- [ ] Measure texture repetition
- [ ] Measure texture uniformity

---

# Phase 6 - Frequency Analysis
- [ ] Learn DCT basics
- [ ] Learn FFT basics
- [ ] Convert image to frequency domain
- [ ] Analyze high-frequency energy
- [ ] Detect spectral anomalies

---

# Phase 7 - OpenMP Parallelization
- [ ] Parallelize pixel loops
- [ ] Parallelize block processing
- [ ] Use reduction for shared metrics
- [ ] Benchmark sequential vs OpenMP
- [ ] Test different thread counts

---

# Phase 8 - Scoring System
- [ ] Create weighted scoring model
- [ ] Combine all feature scores
- [ ] Output AI likelihood percentage
- [ ] Create analysis summary

---

# Phase 9 - Benchmarking
- [ ] Benchmark small images
- [ ] Benchmark medium images
- [ ] Benchmark large images
- [ ] Measure speedup
- [ ] Measure scaling efficiency

---

# Phase 10 - Optional Extensions
- [ ] Add CUDA acceleration
- [ ] Add Python bindings
- [ ] Add FastAPI backend
- [ ] Add frontend dashboard
- [ ] Add ML classifier later

---

# Notes

Focus first on:
1. Correctness
2. Understanding algorithms
3. Parallelization
4. Benchmarking

Do NOT focus on perfect AI detection accuracy initially.