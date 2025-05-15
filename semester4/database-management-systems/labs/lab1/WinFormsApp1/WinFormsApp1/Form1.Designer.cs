namespace WinFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            dataGridView1 = new DataGridView();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            AddButton = new Button();
            button2 = new Button();
            dataGridView2 = new DataGridView();
            button1 = new Button();
            button3 = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(33, 161);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 123;
            dataGridView1.Size = new Size(718, 650);
            dataGridView1.TabIndex = 0;
            dataGridView1.CellClick += dataGridView1_CellClick;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15F);
            label1.Location = new Point(1625, 218);
            label1.Name = "label1";
            label1.Size = new Size(169, 28);
            label1.TabIndex = 1;
            label1.Text = "DepartmentName";
            label1.Click += label1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 15F);
            label2.Location = new Point(1625, 397);
            label2.Name = "label2";
            label2.Size = new Size(178, 28);
            label2.TabIndex = 2;
            label2.Text = "EmployeesNumber";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 15F);
            label3.Location = new Point(1625, 588);
            label3.Name = "label3";
            label3.Size = new Size(65, 28);
            label3.TabIndex = 3;
            label3.Text = "CityID";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(1879, 218);
            textBox1.Multiline = true;
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(357, 106);
            textBox1.TabIndex = 5;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(1879, 397);
            textBox2.Multiline = true;
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(357, 106);
            textBox2.TabIndex = 6;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(1879, 588);
            textBox3.Multiline = true;
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(357, 106);
            textBox3.TabIndex = 7;
            // 
            // AddButton
            // 
            AddButton.Font = new Font("Segoe UI", 11F);
            AddButton.Location = new Point(1951, 857);
            AddButton.Name = "AddButton";
            AddButton.Size = new Size(239, 102);
            AddButton.TabIndex = 9;
            AddButton.Text = "Add";
            AddButton.UseVisualStyleBackColor = true;
            AddButton.Click += AddButtonClick;
            // 
            // button2
            // 
            button2.Font = new Font("Segoe UI", 11F);
            button2.Location = new Point(33, 23);
            button2.Name = "button2";
            button2.Size = new Size(231, 86);
            button2.TabIndex = 10;
            button2.Text = "Display data";
            button2.UseVisualStyleBackColor = true;
            button2.Click += DisplayDataButtonClick;
            // 
            // dataGridView2
            // 
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView2.Location = new Point(846, 161);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.RowHeadersWidth = 123;
            dataGridView2.Size = new Size(700, 650);
            dataGridView2.TabIndex = 11;
            dataGridView2.CellContentClick += dataGridView2_CellContentClick;
            // 
            // button1
            // 
            button1.Location = new Point(906, 857);
            button1.Name = "button1";
            button1.Size = new Size(239, 102);
            button1.TabIndex = 12;
            button1.Text = "Update";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button3
            // 
            button3.Location = new Point(1193, 857);
            button3.Name = "button3";
            button3.Size = new Size(239, 102);
            button3.TabIndex = 13;
            button3.Text = "Delete";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // Form1
            // 
            ClientSize = new Size(2270, 979);
            Controls.Add(button3);
            Controls.Add(button1);
            Controls.Add(dataGridView2);
            Controls.Add(button2);
            Controls.Add(AddButton);
            Controls.Add(textBox3);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(dataGridView1);
            Name = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }
        private DataGridView dataGridView2;
        private Button button1;
        private Button button3;
    }
}