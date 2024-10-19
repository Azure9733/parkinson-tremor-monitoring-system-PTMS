#workingggggg code - FINAL
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
filename="enter_file_name_here"

# Lists to hold the data
time = []
y_coords = [] #for signal
envelope = []

#getting appropriate lower and upper limits for y-axis
y=[] #list to store y-values
lim=500
Ulim=500
Llim=-500
file=open(filename,'r')
for line in file:
    # split by comma
    parts = line.split(',')
    # Ensure we have exactly three parts
    y.append(int(parts[1]))  # signal
for j in y:
    if j>Ulim:
        Ulim=j
    if j<Llim:
        Llim=j
file.close()
if abs(Ulim)>abs(Llim):
    lim=abs(Ulim)
else:
    lim=abs(Llim)
lim=(lim+0.05*lim)


file=open(filename,'r')
#fucntion to animate
def animate(i):
    #reading data from file
    line=file.readline()
    # split by comma
    parts = line.split(',')
    # Ensure we have exactly three parts
    if len(parts) == 3:
        time.append(int(parts[0]))  # Assuming time is an integer
        y_coords.append(int(parts[1]))  # signal
        envelope.append(int(parts[2]))  # envelope
        
    plt.cla()  # Clear the current axes
    #PLOT DATA
    plt.plot(time, y_coords, label='Signal')
    plt.plot(time, envelope,label='Envelope')
    #LABELS and TITLES
    plt.title('EMG Data over Time')
    plt.xlabel('Time\n(in milliseconds)')
    plt.ylabel('Coordinates')

    plt.ylim(-lim, +lim)  # Set the y-axis limit
    plt.legend(loc='upper right') #legends never die
    
ani = FuncAnimation(plt.gcf(), animate, interval=5)
manager = plt.get_current_fig_manager()
manager.full_screen_toggle()
plt.show()
file.close()
