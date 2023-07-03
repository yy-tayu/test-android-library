package com.fotric.jdenali.bean;

import java.nio.ByteBuffer;

public class JImage {
    private ByteBuffer data;
    private int linesize;
    private int width;
    private int height;
    private int channel;
    private int depth;
    private int offset;

    public ByteBuffer getData() {
        return data;
    }

    public void setData(ByteBuffer data) {
        this.data = data;
    }

    public int getLinesize() {
        return linesize;
    }

    public void setLinesize(int linesize) {
        this.linesize = linesize;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public int getChannel() {
        return channel;
    }

    public void setChannel(int channel) {
        this.channel = channel;
    }

    public int getDepth() {
        return depth;
    }

    public void setDepth(int depth) {
        this.depth = depth;
    }

    public int getOffset() {
        return offset;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }

    public JImage(JImage other) {
        this.data = other.data;
        this.width = other.width;
        this.height = other.height;
        this.channel = other.channel;
        this.depth = other.depth;
        this.linesize = other.linesize;
        this.offset = other.offset;
    }

    public JImage(ByteBuffer data, int width, int height, int channel, int depth, int offset) {
        this.data = data;
        this.width = width;
        this.height = height;
        this.channel = channel;
        this.depth = depth;
        this.linesize = width * (channel * depth / 8);
        this.offset = offset;
    }

    public JImage(int width, int height, int channel, int depth, int offset) {
        this.width = width;
        this.height = height;
        this.channel = channel;
        this.depth = depth;
        this.linesize = width * (channel * depth / 8);
        this.offset = offset;
    }

    public JImage clone() {
        ByteBuffer newData = ByteBuffer.allocateDirect(data.capacity());
        newData.put(data);
        newData.rewind();
        return new JImage(newData, width, height, channel, depth, offset);
    }

    static public JImage create(int width, int height, int channel, int depth, int offset) {
        int bufferSize = width * height * channel;
        ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
        return new JImage(buffer, width, height, channel, depth, offset);
    }

    static public JImage create(int width, int height, int channel) {
        int bufferSize = width * height * channel;
        ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
        return new JImage(buffer, width, height, channel, 0, 0);
    }

    @Override
    public String toString() {
        return "JImage{" +
                "data length=" + (data != null ? data.remaining() : "data is null") +
                ", linesize=" + linesize +
                ", width=" + width +
                ", height=" + height +
                ", channel=" + channel +
                ", depth=" + depth +
                ", offset=" + offset +
                '}';
    }
}
