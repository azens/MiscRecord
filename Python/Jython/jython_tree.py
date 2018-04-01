import java
import javax
import org
import sun
import com

package_type = type(java)


def classtree(root, level=0):
    for ele in dir(root):
        if package_type == type(getattr(root, ele)):
            print ' '*4*level, ele
            classtree(getattr(root, ele), level+1)


try:
    print '[java]'
    classtree(java)
    print '[javax]'
    classtree(javax)
    print '[org]'
    classtree(org)
    print '[sun]'
    classtree(sun)
    print '[com]'
    classtree(com)
except:
    None
