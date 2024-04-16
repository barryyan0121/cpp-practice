FROM ubuntu:latest

# ARM64 requires ubuntu-ports
RUN sed -i 's/http:\/\/ports.ubuntu.com/http:\/\/mirrors.tuna.tsinghua.edu.cn\/ubuntu-ports/g' /etc/apt/sources.list

# RUN pip install --upgrade pip
# RUN pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    locales \
    gdb \
    g++ \
    cmake \
    make \
    zsh \
    git \
    curl
    # wget && \
    # apt-get clean && \
    # rm -rf /var/lib/apt/lists/*

# Generate locale
RUN locale-gen en_US.UTF-8 && \
    update-locale LANG=en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US:en
ENV LC_ALL en_US.UTF-8

# Install Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended || echo "Oh My Zsh installation failed"

# Set the default shell to zsh
RUN chsh -s $(which zsh)

# Install Oh My Zsh plugins
## Here we install the 'zsh-autosuggestions' plugin as an example
RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions && \
    git clone https://github.com/zsh-users/zsh-syntax-highlighting ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting


# Copy your custom zsh configuration file into the container
COPY .zshrc /root/.zshrc

WORKDIR /app

# Copy just the entrypoint script and ensure it is executable
COPY entrypoint.sh /app/
RUN chmod +x /app/entrypoint.sh

# Copy the rest of the application files
COPY .  .

ENTRYPOINT ["/app/entrypoint.sh"]
