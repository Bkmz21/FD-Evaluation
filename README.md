## Compact Convolutional Neural Network Cascade ##


### Evaluation of frontal face detection algorithms ###

This is an implementation of the algorithm described in the following paper:

	I.A. Kalinowski, V.G. Spitsyn,
	Compact Convolutional Neural Network Cascade for Face Detection,
	http://arxiv.org/abs/1508.01292

If you use the provided code/binaries or data for your work, please cite this paper. 

##
Demo video:

- [4K Ultra HD](https://www.youtube.com/watch?v=Ad6GxIR8EpU)
- [Full HD](https://www.youtube.com/watch?v=xE8sG0gyAkc)
- [HD](https://www.youtube.com/watch?v=xVNRXH4n-ks)

##
The precision detection can be increased by combination detectors.

<table>
  <tr align=center>
	<td>№</td>
    <td>method</td>
    <td>true</td> 
    <td>false</td>
	<td>recall</td>
    <td>precision</td>
	<td>mean&nbsp;time,&nbsp;ms</td>
	<td>min&nbsp;time,&nbsp;ms</td>
	<td>max&nbsp;time,&nbsp;ms</td>
	<td>demo</td>
  </tr>
  <tr align=center>
	<td>1</td>
    <td>Viola–Jones*</td>
    <td>18679</td> 
    <td>3587</td>
	<td>46.7%</td>
    <td>83.9%</td>
	<td>118</td>
	<td>79</td>
	<td>136</td>
	<td><a href="https://cloud.mail.ru/public/GyYo/wtPUGvnzL">HD</a></td>
  </tr>
  <tr align=center>
	<td>2</td>
    <td>Compact&nbsp;CNN</td T1=T2=0.5>
    <td>18788</td> 
    <td>908</td>
	<td>47.0%</td>
    <td>95.4%</td>
	<td>12</td>
	<td>10</td>
	<td>17</td>
	<td><a href="https://cloud.mail.ru/public/GyYo/wtPUGvnzL">HD</a></td>
  </tr>
  <tr align=center>
	<td>3</td>
    <td>Compact&nbsp;CNN<br>(optimized&nbsp;for&nbsp;precision)</td T1=T2=0.5 tcd=3>
    <td>16627</td> 
    <td>379</td>
	<td>41.6%</td>
    <td>97.8%</td>
	<td>12</td>
	<td>10</td>
	<td>17</td>
	<td></td>
  </tr>
  <tr align=center>
	<td>4</td>
    <td>Hybrid** (1&nbsp;&&nbsp;2)</td>
    <td>16684</td> 
    <td>93</td>
	<td>41.7%</td>
    <td>99.4%</td>
	<td>17</td>
	<td>10</td>
	<td>800</td>
	<td><a href="https://cloud.mail.ru/public/hcTv/eSaXavD1F">HD</a></td>
  </tr>
</table>
*OpenCV 3.0.0 <a href="https://github.com/Itseez/opencv/tree/master/data/haarcascades_cuda">haarcascade frontalface alt for cuda</a><br>
**without code optimization<br><br>
Running on GPU Nvidia GeForce GT 640M, CPU Intel Core i7-3610QM (2.3GHz, without Turbo Boost)<br>
Search settings: minSize – 40×40, scaleFactor – 1.2, minNeighbors – 2, without tracking<br>

## Contact

For any additional information contact me at <kua_21@mail.ru>.

Copyright (c) 2015, Ilya Kalinowski.
All rights reserved.



