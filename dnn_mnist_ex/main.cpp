#include <dlib/dnn.h>
#include <iostream>
#include <dlib/data_io.h>

using namespace std;
using namespace dlib;

int main(int argc, char** argv) try
{
    if (argc != 2)
    {
        cout << "This example needs the MNIST dataset to run!" << endl;
        cout << "You can get MNIST from http://yann.lecun.com/exdb/mnist/" << endl;
        cout << "Download the 4 files that comprise the dataset, decompress them, and" << endl;
        cout << "put them in a folder.  Then give that folder as input to this program." << endl;
        return 1;
    }

    std::vector<matrix<unsigned char> > training_images;
    std::vector<unsigned long> training_labels;
    std:vector<matrix<unsigned char> > testing_images;
    std::vector<unsigned long> testing labels;
    load_mnist_dataset(argv[1], training_images, training_labels, testing_images, testing_labels);

    using net_type = loss_multiclass_log<
                                fc<10,
                                relu<fc<84,
                                relu<fc<120,
                                max_pool<2,2,2,2,relu<con<16,5,5,1,1,
                                max_pool<2,2,2,2,relu<con<6,5,5,1,1,
                                input<matrix<unsigned char>>
                                >>>>>>>>>>>>;

    net_type net;
    dnn_trainer<net_type> trainer(net);
    trainer.set_learning_rate(0.01);
    trainer.set_min_learning_rate(0.00001);
    trainer.set_mini_batch_size(128);
    trainer.be_verbose();
    trainer.set_synchronization_file("mnist_sync", std::chrono::seconds(20));

    trainer.train(training_images, training_labels);

    net.clean();
    serialize("mnist_network.dat") << net;

    std::vector<unsigned long> predicted_labels = net(training_imges);
    int num_right = 0;
    int num_wrong = 0;

    for(size_t i = 0; i < training_images.size(); ++i)
    {
        if(predicted_labels[i] == training_labels[i])
            ++num_right;
        else
            ++num_wrong;
    }
    cout << "training num_right " << num_right << endl;
    cout << "training num_wrong " << num_wrong << endl;
    cout << "training accuracy " << num_right / (double)(num_right + num_wrong) << endl;

    predicted_labels = net(testing_images);
    num_right = 0;
    num_wrong = 0;

    for(size_t i = 0; i < testing_images.size(); ++i)
    {
        if(predicted_labels[i] == testing_labels[i])
            ++num_right;
        else
            ++num_wrong;
    }
    cout << "testing num_right: " << num_right << endl;
    cout << "testing num_wrong: " << num_wrong << endl;
    cout << "testing accuracy: " << num_right / (double)(num_right)

    return 0;
}
