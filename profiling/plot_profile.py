import matplotlib.pyplot as plt
import numpy as np

dat = np.loadtxt("prof_fit_maxnop32.dat")
dat2 = np.loadtxt("prof_fit_maxnop8.dat")
print dat
plt.semilogy(dat[:,0], 10**6 * dat[:,1], 'o', alpha=0.15, color="darkolivegreen", label=r"Max. Matrix dimension $32 \times 32$")
plt.semilogy(dat2[:,0], 10**6 *  dat2[:,1], 's', alpha=0.15, color="mediumslateblue", label=r"Max. Matrix dimension $8 \times 8$")
plt.xlabel("Number of hits in fit")
plt.ylabel(r"Fit CPU time [$\mu$s]")
plt.title("TrickTrack RiemannFit CPU Performance - Random Input")
plt.legend(loc="best")
plt.savefig("tricktrack_riemann_cpu.png")
plt.savefig("tricktrack_riemann_cpu.pdf")
plt.show()
