from PIL import Image  
from pylab import *  
import os

def piclist(folder):
	output = open('index.txt', 'w+')
	for root,directors,files in os.walk(folder):
		for filename in files:
			if filename.endswith(".jpg") or filename.endswith(".jpeg") or filename.endswith(".png")or filename.endswith(".pgm"):
				im = array(Image.open(filename))	
				imshow(im)  
				output.write(filename)
				output.write('\n')
				print 'Please click 2 points'  
				result = ""
				x =ginput(2)  
				print 'you clicked:',x 
				result += str(int(x[0][0]+0.5))+" "+str(int(x[0][1]+0.5))+" "+str(int(x[1][0]+0.5))+" "+str(int(x[1][1]+0.5))
				print result
				output.write(result)
				output.write('\n')
				plt.close('all')

				
if __name__ == '__main__':
    piclist('E:/Code/CV_eigenface/CV_eigenface/faces')