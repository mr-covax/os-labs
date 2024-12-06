FROM ubuntu:noble

ENV DEBIAN_FRONTEND noninteractive

RUN apt update && apt install -y \
	gcc \
	g++ \
	binutils \
	cmake \
	git \
	fish \
	curl

RUN rm -rf /var/lib/apt/lists/*
RUN chsh -s /usr/bin/fish