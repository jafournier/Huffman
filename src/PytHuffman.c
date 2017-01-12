#include<Python.h>
#include<sstream>
#include<vector>
#include<string>
#include"HuffTree.h"
using namespace std;



static PyObject* getCode(PyObject *self,PyObject* args){
  /* wrapper function to get C- huffman encoding
  */
    PySys_WriteStdout("in function getCode c++");
    PyObject * listObj;
    if (! PyArg_ParseTuple( args, "O!", &PyList_Type, &listObj ))
        return NULL;
    vector<float> input;
    int n = PyList_Size(listObj);
    input.resize(n);
    int arg_int;
    if(!n){
         // empty list, quit
         PySys_WriteStdout("empty list \n");
         return NULL;
    }
    if(PyInt_Check(PyList_GetItem(listObj, 0))){
        // test if we have a list of int
        for(int i =0; i < n; i++){
            PyArg_Parse(PyList_GetItem(listObj, i),"i", &arg_int);
            input[i] = float(arg_int);
            //cout << " recorded at " << i <<" : "<< input[i] << " \n "; // DEBUG 
        }
    }else if(PyFloat_Check(PyList_GetItem(listObj, 0))){
        // test if we have a list of float
        for(int i =0; i < n; i++){
            PyArg_Parse(PyList_GetItem(listObj, i),"f", &input[i]);
            //cout << " recorded at " << i <<" : "<< input[i] << " \n "; // DEBUG 
        }
    }
    HuffTree huff(input);
    vector<string> c_output(huff.getEncodeStringTable());
    PyObject * pyt_output = PyList_New(n) ;
    for(int i =0; i < n; i++){
       PyList_SetItem(pyt_output, i, Py_BuildValue("s",c_output[i].c_str()));
       //cout << " put the output on python " << i <<" \n "; // DEBUG 
    }
    return pyt_output;
}


static PyMethodDef PytMethods[] = {
    {"getCode",  getCode, METH_VARARGS,"get huffman encoding"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};


PyMODINIT_FUNC
inithuffman(void){
    (void) Py_InitModule("huffman",PytMethods);
}
