APPS =				\
	main			\

CFLAGS  = -g -Wall

CFLAGS  += `pkg-config gtk4 --cflags`
LDFLAGS += `pkg-config gtk4 --libs`

all: $(APPS)

clean:
	$(RM): $(APPS)
