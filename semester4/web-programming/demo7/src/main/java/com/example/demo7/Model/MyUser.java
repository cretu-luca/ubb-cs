package com.example.demo7.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "MyUser")
public class MyUser {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public String Username;
}
