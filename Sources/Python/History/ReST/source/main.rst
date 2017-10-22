Hello World!
============
.. code-block:: c
   :emphasize-lines: 3,5

	#include <float.h>
	#include <stdio.h>

	int main(void)
	{
	   printf("DBL_EPSILON is %.*g\n", DBL_DIG, DBL_EPSILON);
	   return 0;
	} 

.. math::

  W^{3\beta}_{\delta_1 \rho_1 \sigma_2} \approx U^{3\beta}_{\delta_1 \rho_1}
.. plot::

   import matplotlib.pyplot as plt
   import numpy as np
   x = np.random.randn(1000)
   plt.hist( x, 20)
   plt.grid()
   plt.title(r'Normal: $\mu=%.2f, \sigma=%.2f$'%(x.mean(), x.std()))
   plt.show()