package com.example.demo7.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "MyOrder")
public class MyOrder {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public int UserId;
    public double TotalPrice;
}
