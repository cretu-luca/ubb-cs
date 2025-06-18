package com.example.demo7.Model;

import jakarta.persistence.*;

@Entity
@Table(name = "MyOrderItem")
public class MyOrderItem {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    public int Id;
    public int OrderId;
    public int ProductId;
}
