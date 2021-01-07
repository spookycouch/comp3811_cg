import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

# sine curve
PI = np.pi
x = np.linspace(-2, 2, 1000)
y = np.sin(x*PI)

# amplitude
amplitude = 60
y *= amplitude

# axis
ax = plt.subplot()
ax.plot(x,y)
ax.xaxis.set_major_formatter(ticker.StrMethodFormatter('{x}\u03C0'))
ax.set_xlabel('distance')
ax.set_ylabel('light bulb angle')
plt.show()


# circle
x = np.sin(np.linspace(-1,1,1000) * PI)
y = np.cos(np.linspace(-1,1,1000) * PI)

ax = plt.subplot()
ax.plot(x,y)

an_x = [0,1,0,-1]
an_y = [1,0,-1,0]
ax.scatter(an_x,an_y)
ax.annotate('\u03B8=0\nsin(\u03B8)=0\ncos(\u03B8)=1'            , (an_x[0] * 1.0, an_y[0] * 0.7))
ax.annotate('\u03B8=1.5\u03C0\nsin(\u03B8)=-1\ncos(\u03B8)=0'   , (an_x[1] * 0.7, an_y[1] * 1.0))
ax.annotate('\u03B8=\u03C0\nsin(\u03B8)=0\ncos(\u03B8)=-1'      , (an_x[2] * 1.0, an_y[2] * 0.8))
ax.annotate('\u03B8=0.5\u03C0\nsin(\u03B8)=1\ncos(\u03B8)=0'    , (an_x[3] * 0.9, an_y[3] * 1.0))
ax.set_xlabel('x')
ax.set_ylabel('y')
plt.show()