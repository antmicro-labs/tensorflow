# Copyright 2019 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
#
# THIS IS A GENERATED DOCKERFILE.
#
# This file was assembled from multiple pieces, whose use is documented
# throughout. Please refer to the TensorFlow dockerfiles documentation
# for more information.

ARG UBUNTU_VERSION=18.04

FROM ubuntu:${UBUNTU_VERSION} as base

RUN apt-get update && apt-get install -y curl

# See http://bugs.python.org/issue19846
ENV LANG C.UTF-8

RUN apt-get update && apt-get install -y \
    python3
    python3-pip

RUN python3 -m pip --no-cache-dir install --upgrade \
    pip \
    setuptools

# Some TF tools expect a "python" binary
RUN ln -s $(which python3) /usr/local/bin/python

# Options:
#   tensorflow
#   tensorflow-gpu
#   tf-nightly
#   tf-nightly-gpu
# Set --build-arg TF_PACKAGE_VERSION=1.11.0rc0 to install a specific version.
# Installs the latest version by default.
ARG TF_PACKAGE=tensorflow
ARG TF_PACKAGE_VERSION=
RUN ${PIP} install --no-cache-dir ${TF_PACKAGE}${TF_PACKAGE_VERSION:+==${TF_PACKAGE_VERSION}}

# install libnuma, openssh, wget
RUN ( apt-get update && apt-get install -y --no-install-recommends --fix-missing \
        libnuma-dev \
        openssh-server \
        openssh-client \
        wget && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* ) || \
    ( yum -y update && yum -y install \
            numactl-devel \
            openssh-server \
            openssh-clients \
            wget && \
    yum clean all ) || \
    ( echo "Unsupported Linux distribution. Aborting!" && exit 1 )

# Install Open MPI
# download realese version from official website as openmpi github master is not always stable
ARG OPENMPI_VERSION=openmpi-4.0.0
ARG OPENMPI_DOWNLOAD_URL=https://www.open-mpi.org/software/ompi/v4.0/downloads/openmpi-4.0.0.tar.gz
RUN mkdir /tmp/openmpi && \
    cd /tmp/openmpi && \
    wget ${OPENMPI_DOWNLOAD_URL} && \
    tar zxf ${OPENMPI_VERSION}.tar.gz && \
    cd ${OPENMPI_VERSION} && \
    ./configure --enable-orterun-prefix-by-default && \
    make -j $(nproc) all && \
    make install && \
    ldconfig && \
    rm -rf /tmp/openmpi

# Create a wrapper for OpenMPI to allow running as root by default
RUN mv /usr/local/bin/mpirun /usr/local/bin/mpirun.real && \
    echo '#!/bin/bash' > /usr/local/bin/mpirun && \
    echo 'mpirun.real --allow-run-as-root "$@"' >> /usr/local/bin/mpirun && \
    chmod a+x /usr/local/bin/mpirun

# Configure OpenMPI to run good defaults:
RUN echo "btl_tcp_if_exclude = lo,docker0" >> /usr/local/etc/openmpi-mca-params.conf

# Install OpenSSH for MPI to communicate between containers
RUN mkdir -p /var/run/sshd

# Allow OpenSSH to talk to containers without asking for confirmation
RUN cat /etc/ssh/ssh_config | grep -v StrictHostKeyChecking > /etc/ssh/ssh_config.new && \
    echo "    StrictHostKeyChecking no" >> /etc/ssh/ssh_config.new && \
    mv /etc/ssh/ssh_config.new /etc/ssh/ssh_config

# Install Horovod
ARG HOROVOD_VERSION=0.16.4
RUN ${PIP} install --no-cache-dir horovod==${HOROVOD_VERSION}

COPY bashrc /etc/bash.bashrc
RUN chmod a+rwx /etc/bash.bashrc
