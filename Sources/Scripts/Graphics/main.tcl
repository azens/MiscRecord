#!/mingw32/bin/tclsh 
proc factorial {val} {
	set result 1
	while {$val>0} {
	set result [expr $result*$val]
	incr val -1
	}
	return $result
}
puts stdout [factorial 100]
