package com.example.demo.Model;

public class Document {
    private int id;
    private String name;
    private String contents;

    public Document(int id, String name, String contents) {
        this.id = id;
        this.name = name;
        this.contents = contents;
    }

    public int getId() { return id; }
    public String getName() { return name; }
    public String getContents() { return contents; }
}