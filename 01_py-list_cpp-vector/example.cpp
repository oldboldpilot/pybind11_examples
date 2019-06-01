#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
#include <tbb/concurrent_unordered_map.h>
#include <tbb/concurrent_vector.h>
#include <tbb/parallel_for.h>
#include <iostream>
#include <algorithm>
#include <Python.h>
#include <utility>
using namespace pybind11;
using namespace tbb;
using namespace std;


// ----------------
// Regular C++ code
// ----------------

// multiply all entries by 2.0
// input:  std::vector ([...]) (read only)
// output: std::vector ([...]) (new copy)
std::vector<double> modify(const std::vector<double>& input)
{
  std::vector<double> output;

  std::transform(
    input.begin(),
    input.end(),
    std::back_inserter(output),
    [](double x) -> double { return 2.*x; }
  );
  return output;
}

std::vector<double> change(const std::vector<double> & input)
{
  
  size_t n = (size_t) input.size();
  std::vector<double> output(n);
  PyEval_InitThreads();
  Py_BEGIN_ALLOW_THREADS

  tbb::parallel_for(size_t(0), n, [&](size_t i) {output[i]=input[i]*2.0;});
  Py_END_ALLOW_THREADS
  return output;

}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  m.def("modify", &modify, "Multiply all entries of a list by 2.0");
  m.def("change",&change,"test parallel_for");
}
