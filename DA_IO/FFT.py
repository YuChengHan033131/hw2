import matplotlib.pyplot as plt
import numpy as np
import serial

sample=220
scr =serial.Serial('/dev/ttyACM0')
y=np.arange(0,1,1.0/sample)
t= np.arange(0,1,1.0/sample)
k = np.arange(sample)
frq=np.arange(sample/2)
frq=frq[range(int(sample/2))]
for i in range(0,sample):
    y[i]=float(scr.readline())

Y = np.fft.fft(y)/sample*2
Y = Y[range(int(sample/2))]

fig, ax = plt.subplots(2, 1)
ax[0].plot(t,y)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')
ax[1].plot(frq,abs(Y),'r')
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')
plt.show()
scr.close()