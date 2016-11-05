//
// Created by ss on 16-11-2.
//

#ifndef MASCOT_SVM_SVMMODEL_H
#define MASCOT_SVM_SVMMODEL_H

#include <vector>
#include "../svm-shared/gpu_global_utility.h"
#include "svmProblem.h"
#include "svmParam.h"

using std::vector;

class svmModel {
private:
    SVMParam param;
    unsigned int nrClass;
    unsigned int cnr2;
    vector<vector<vector<float_point> > > supportVectors;
    vector<vector<float_point> > coef;
    vector<float_point> rho;
    vector<float_point> probA;
    vector<float_point> probB;
    vector<int> label;
    bool probability;

    unsigned int inline getK(int i, int j) const;

    float_point *predictLabels(const float_point *kernelValues, int, int) const;

    float_point *ComputeClassLabel(int nNumofTestSamples,
                                   float_point *pfDevSVYiAlphaHessian, const int &nNumofSVs,
                                   float_point fBias, float_point *pfFinalResult) const;

    void computeKernelValuesOnFly(const vector<vector<float_point> > &samples,
                                  const vector<vector<float_point> > &supportVectors, float_point *kernelValues) const;

    void addBinaryModel(const svmProblem &, const svm_model &, int i, int j);

    float_point sigmoid_predict(float_point decValue, float_point A, float_point B) const;

    void multiclass_probability(const vector<vector<float_point> > &, vector<float_point> &) const;

    void
    sigmoidTrain(const float_point *decValues, const int, const vector<int> &labels, float_point &A, float_point &B);

public:

    void fit(const svmProblem &problem, const SVMParam &param);

    vector<int> predict(const vector<vector<float_point> > &, bool probability=false) const;

    vector<vector<float_point> > predictProbability(const vector<vector<float_point> > &) const;

    void predictValues(const vector<vector<float_point> > &, vector<float_point *> &) const;
};


#endif //MASCOT_SVM_SVMMODEL_H