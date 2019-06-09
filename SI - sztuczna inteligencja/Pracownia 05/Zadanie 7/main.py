# autoencoder_anom_mnist.py
# anomaly detection for the MNIST digits
# Keras 2.2.4, Tensorflow 1.11.0
# Anaconda3 5.2.0 (Python 3.6.5)

import numpy as np
import keras as K
import matplotlib.pyplot as plt
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'  # suppress CPU msg

# -----------------------------------------------------------


def display(raw_data_x, raw_data_y, idx):
    label = raw_data_y[idx]  # like '5'
    print("digit = ", str(label), "\n")
    pixels = np.array(raw_data_x[idx])  # target row of pixels
    pixels = pixels.reshape((28, 28))
    plt.rcParams['toolbar'] = 'None'
    plt.imshow(pixels, cmap=plt.get_cmap('gray_r'))
    plt.show()

# -----------------------------------------------------------


class MyLogger(K.callbacks.Callback):
    def __init__(self, n):
        self.n = n   # print loss every n epochs

    def on_epoch_end(self, epoch, logs={}):
        if epoch % self.n == 0:
            curr_loss = logs.get('loss')
            print("epoch = %4d loss = %0.6f" % (epoch, curr_loss))

# -----------------------------------------------------------


def main():
    # 0. get started
    print("\nBegin MNIST anomaly detect using an autoencoder \n")

    # 1. load data into memory
    # format: 7 ** 0 255 67 . . 123 (digit, **, 784 pixel values)
    print("Loading partial MNIST Dataset into memory \n")
    data_file = ".\\mnist_keras_1000.txt"
    data_x = np.loadtxt(data_file, delimiter=" ",
                        usecols=range(2, 786), dtype=np.float32)
    labels = np.loadtxt(data_file, delimiter=" ",
                        usecols=[0], dtype=np.float32)
    norm_x = data_x / 255
    print(f'\nLoaded {len(norm_x)} images!\n')

    # 2. define autoencoder model
    print("Creating a 784-100-50-100-784 autoencoder \n")
    my_init = K.initializers.glorot_uniform(seed=1)
    autoenc = K.models.Sequential()
    autoenc.add(K.layers.Dense(input_dim=784, units=100,
                               activation='tanh', kernel_initializer=my_init))
    autoenc.add(K.layers.Dense(units=50,
                               activation='tanh', kernel_initializer=my_init))
    autoenc.add(K.layers.Dense(units=100,
                               activation='tanh', kernel_initializer=my_init))
    autoenc.add(K.layers.Dense(units=784,
                               activation='tanh', kernel_initializer=my_init))

    # 3. compile model
    simple_adam = K.optimizers.adam()
    autoenc.compile(loss='mean_squared_error',
                    optimizer=simple_adam)

    # 4. train model
    print("Starting training")
    max_epochs = 400
    my_logger = MyLogger(n=100)
    autoenc.fit(norm_x, norm_x, batch_size=40, epochs=max_epochs, verbose=0, callbacks=[my_logger])
    print("Training complete")

    # 5. find most anomalous data item
    N = len(norm_x)
    max_se = 0.0
    max_ix = 0
    predicteds = autoenc.predict(norm_x)
    ANOMALIES = []
    for i in range(N):
        diff = norm_x[i] - predicteds[i]
        curr_se = np.sum(diff * diff)
        ANOMALIES.append((curr_se, i))
        if curr_se > max_se:
            max_se = curr_se
            max_ix = i

    ANOMALIES.sort(reverse=True)

    # raw_data_x = data_x.astype(np.int)
    # raw_data_y = labels.astype(np.int)
    raw_data_x = data_x
    raw_data_y = labels

    print("\nMost anomalous digit is at index ", max_ix)
    display(raw_data_x, raw_data_y, max_ix)

    for a in ANOMALIES[1:10]:
        display(raw_data_x, raw_data_y, a[1])


if __name__ == "__main__":
    main()
