noinst_LIBRARIES = libcore.a
libcore_a_SOURCES = core.cpp edma.cpp m_unit.cpp test_s_unit.cpp \
  dbg.cpp l2_mem_ctrl.cpp n_unit.cpp timer_32bit.cpp \
  d_unit.cpp l_unit.cpp s_unit.cpp unit.cpp

#libcore_a_LIBADD = libjit

AM_CPPFLAGS = -I$(srcdir)/../../ \
  -I$(srcdir)/../../libjit/include/ \
  -DCORE_ALL_SPEED
