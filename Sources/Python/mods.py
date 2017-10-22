>>> dir
<built-in function dir>
>>> dir()
['__builtins__', '__doc__', '__name__', '__package__']
>>> dir(__builtins__)
['ArithmeticError', 'AssertionError', 'AttributeError', 'BaseException', 'Buffer
Error', 'BytesWarning', 'DeprecationWarning', 'EOFError', 'Ellipsis', 'Environme
ntError', 'Exception', 'False', 'FloatingPointError', 'FutureWarning', 'Generato
rExit', 'IOError', 'ImportError', 'ImportWarning', 'IndentationError', 'IndexErr
or', 'KeyError', 'KeyboardInterrupt', 'LookupError', 'MemoryError', 'NameError',
 'None', 'NotImplemented', 'NotImplementedError', 'OSError', 'OverflowError', 'P
endingDeprecationWarning', 'ReferenceError', 'RuntimeError', 'RuntimeWarning', '
StandardError', 'StopIteration', 'SyntaxError', 'SyntaxWarning', 'SystemError',
'SystemExit', 'TabError', 'True', 'TypeError', 'UnboundLocalError', 'UnicodeDeco
deError', 'UnicodeEncodeError', 'UnicodeError', 'UnicodeTranslateError', 'Unicod
eWarning', 'UserWarning', 'ValueError', 'Warning', 'WindowsError', 'ZeroDivision
Error', '_', '__debug__', '__doc__', '__import__', '__name__', '__package__', 'a
bs', 'all', 'any', 'apply', 'basestring', 'bin', 'bool', 'buffer', 'bytearray',
'bytes', 'callable', 'chr', 'classmethod', 'cmp', 'coerce', 'compile', 'complex'
, 'copyright', 'credits', 'delattr', 'dict', 'dir', 'divmod', 'enumerate', 'eval
', 'execfile', 'exit', 'file', 'filter', 'float', 'format', 'frozenset', 'getatt
r', 'globals', 'hasattr', 'hash', 'help', 'hex', 'id', 'input', 'int', 'intern',
 'isinstance', 'issubclass', 'iter', 'len', 'license', 'list', 'locals', 'long',
 'map', 'max', 'memoryview', 'min', 'next', 'object', 'oct', 'open', 'ord', 'pow
', 'print', 'property', 'quit', 'range', 'raw_input', 'reduce', 'reload', 'repr'
, 'reversed', 'round', 'set', 'setattr', 'slice', 'sorted', 'staticmethod', 'str
', 'sum', 'super', 'tuple', 'type', 'unichr', 'unicode', 'vars', 'xrange', 'zip'
]

>>> dir(sys)
['__displayhook__', '__doc__', '__excepthook__', '__name__', '__package__', '__s
tderr__', '__stdin__', '__stdout__', '_clear_type_cache', '_current_frames', '_g
etframe', '_mercurial', 'api_version', 'argv', 'builtin_module_names', 'byteorde
r', 'call_tracing', 'callstats', 'copyright', 'displayhook', 'dllhandle', 'dont_
write_bytecode', 'exc_clear', 'exc_info', 'exc_type', 'excepthook', 'exec_prefix
', 'executable', 'exit', 'exitfunc', 'flags', 'float_info', 'float_repr_style',
'getcheckinterval', 'getdefaultencoding', 'getfilesystemencoding', 'getprofile',
 'getrecursionlimit', 'getrefcount', 'getsizeof', 'gettrace', 'getwindowsversion
', 'hexversion', 'last_traceback', 'last_type', 'last_value', 'long_info', 'maxi
nt', 'maxsize', 'maxunicode', 'meta_path', 'modules', 'path', 'path_hooks', 'pat
h_importer_cache', 'platform', 'prefix', 'ps1', 'ps2', 'py3kwarning', 'setchecki
nterval', 'setprofile', 'setrecursionlimit', 'settrace', 'stderr', 'stdin', 'std
out', 'subversion', 'version', 'version_info', 'warnoptions', 'winver']

>>> dir(os)
['F_OK', 'O_APPEND', 'O_BINARY', 'O_CREAT', 'O_EXCL', 'O_NOINHERIT', 'O_RANDOM',
 'O_RDONLY', 'O_RDWR', 'O_SEQUENTIAL', 'O_SHORT_LIVED', 'O_TEMPORARY', 'O_TEXT',
 'O_TRUNC', 'O_WRONLY', 'P_DETACH', 'P_NOWAIT', 'P_NOWAITO', 'P_OVERLAY', 'P_WAI
T', 'R_OK', 'SEEK_CUR', 'SEEK_END', 'SEEK_SET', 'TMP_MAX', 'UserDict', 'W_OK', '
X_OK', '_Environ', '__all__', '__builtins__', '__doc__', '__file__', '__name__',
 '__package__', '_copy_reg', '_execvpe', '_exists', '_exit', '_get_exports_list'
, '_make_stat_result', '_make_statvfs_result', '_pickle_stat_result', '_pickle_s
tatvfs_result', 'abort', 'access', 'altsep', 'chdir', 'chmod', 'close', 'closera
nge', 'curdir', 'defpath', 'devnull', 'dup', 'dup2', 'environ', 'errno', 'error'
, 'execl', 'execle', 'execlp', 'execlpe', 'execv', 'execve', 'execvp', 'execvpe'
, 'extsep', 'fdopen', 'fstat', 'fsync', 'getcwd', 'getcwdu', 'getenv', 'getpid',
 'isatty', 'kill', 'linesep', 'listdir', 'lseek', 'lstat', 'makedirs', 'mkdir',
'name', 'open', 'pardir', 'path', 'pathsep', 'pipe', 'popen', 'popen2', 'popen3'
, 'popen4', 'putenv', 'read', 'remove', 'removedirs', 'rename', 'renames', 'rmdi
r', 'sep', 'spawnl', 'spawnle', 'spawnv', 'spawnve', 'startfile', 'stat', 'stat_
float_times', 'stat_result', 'statvfs_result', 'strerror', 'sys', 'system', 'tem
pnam', 'times', 'tmpfile', 'tmpnam', 'umask', 'unlink', 'unsetenv', 'urandom', '
utime', 'waitpid', 'walk', 'write']