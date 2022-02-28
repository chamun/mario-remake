build:
	docker build -t mario-remake:latest .

run:
	xhost local:$(shell whoami) && \
	docker run --rm -ti    \
		--net=host           \
		--ipc=host           \
		--device /dev/snd    \
		-e DISPLAY=$$DISPLAY \
		mario-remake         \
	&& xhost -local:$(shell whoami)
