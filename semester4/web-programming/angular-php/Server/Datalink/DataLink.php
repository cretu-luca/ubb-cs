<?php

class DataLink {
    public $host;
    public $username;
    public $password;
    public $database;
    public $conn; 

    function __construct() {
        $this->host = 'localhost';
        $this->username = 'root';
        $this->password = '';
        $this->database = 'RecipesDatabase';
    }

    function connect() {
        $this->conn = new mysqli($this->host, $this->username, $this->password, $this->database);

        if ($this->conn->connect_error) {
            die("Connection failed: " . $this->conn->connect_error);
        }

        return $this->conn;
    }

    function prepare($query) {
        if (!$this->conn) {
            $this->connect();
        }
        return $this->conn->prepare($query);
    }

    function execute($query) {
        if (!$this->conn) {
            $this->connect();
        }
        $result = $this->conn->query($query);
        return $result;
    }

    function close() {
        if ($this->conn) {
            $this->conn->close();
        }
    }
}
?>