#include<bits/stdc++.h>
#include <dlib/svm.h>
#include <dlib/rand.h>
using namespace std;
using namespace dlib;

int main()
{
    // 定义样本和标签
    std::vector<dlib::matrix<double,2,1>> samples;
    std::vector<double> labels;

    // 生成一些随机的数据
    dlib::rand rnd;
    for (int i = 0; i < 3; ++i)
    {
        dlib::matrix<double,2,1> sample;
        sample(0) = rnd.get_random_double();
        sample(1) = rnd.get_random_double();
        samples.push_back(sample);

        // 根据样本的位置生成标签
        if(sample(0)>0.5)
            labels.push_back(+1);
        else
            labels.push_back(-1);
    }

    // 使用径向基函数核的支持向量机进行训练
    typedef dlib::radial_basis_kernel<dlib::matrix<double,2,1>> kernel_type;

    // 创建SVM训练器
    dlib::svm_c_trainer<kernel_type> trainer;

    // 设置C参数
    trainer.set_c(10);

    // 训练SVM
    dlib::decision_function<kernel_type> df = trainer.train(samples, labels);

    // 使用训练好的模型
   for(const auto& sample : samples)
   {
        double prediction = df(sample);
        cout << "sample: " << sample << " , prediction: " << prediction << endl;
   }
    
        return 0;
}
