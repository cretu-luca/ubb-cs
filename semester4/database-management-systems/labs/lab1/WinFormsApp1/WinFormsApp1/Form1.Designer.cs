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
            dgvBrands = new DataGridView();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            AddButton = new Button();
            button2 = new Button();
            dgvCoffees = new DataGridView();
            button1 = new Button();
            button3 = new Button();
            textBox4 = new TextBox();
            label4 = new Label();
            ((System.ComponentModel.ISupportInitialize)dgvBrands).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dgvCoffees).BeginInit();
            SuspendLayout();
            // 
            // dgvBrands
            // 
            dgvBrands.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvBrands.Location = new Point(33, 161);
            dgvBrands.Name = "dgvBrands";
            dgvBrands.RowHeadersWidth = 123;
            dgvBrands.Size = new Size(718, 650);
            dgvBrands.TabIndex = 0;
            dgvBrands.CellClick += dataGridView1_CellClick;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15F);
            label1.Location = new Point(1581, 230);
            label1.Name = "label1";
            label1.Size = new Size(194, 81);
            label1.TabIndex = 1;
            label1.Text = "Name";
            label1.Click += label1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 15F);
            label2.Location = new Point(1581, 397);
            label2.Name = "label2";
            label2.Size = new Size(224, 81);
            label2.TabIndex = 2;
            label2.Text = "Weigth";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 15F);
            label3.Location = new Point(1581, 576);
            label3.Name = "label3";
            label3.Size = new Size(275, 81);
            label3.TabIndex = 3;
            label3.Text = "Available";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(1866, 230);
            textBox1.Multiline = true;
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(597, 106);
            textBox1.TabIndex = 5;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(1866, 397);
            textBox2.Multiline = true;
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(597, 106);
            textBox2.TabIndex = 6;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(1866, 565);
            textBox3.Multiline = true;
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(597, 106);
            textBox3.TabIndex = 7;
            // 
            // AddButton
            // 
            AddButton.Font = new Font("Segoe UI", 11F);
            AddButton.Location = new Point(2184, 974);
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
            // dgvCoffees
            // 
            dgvCoffees.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvCoffees.Location = new Point(846, 161);
            dgvCoffees.Name = "dgvCoffees";
            dgvCoffees.RowHeadersWidth = 123;
            dgvCoffees.Size = new Size(700, 650);
            dgvCoffees.TabIndex = 11;
            dgvCoffees.CellContentClick += dataGridView2_CellContentClick;
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
            // textBox4
            // 
            textBox4.Location = new Point(1866, 742);
            textBox4.Multiline = true;
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(597, 106);
            textBox4.TabIndex = 14;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI", 15F);
            label4.Location = new Point(1590, 754);
            label4.Name = "label4";
            label4.Size = new Size(241, 81);
            label4.TabIndex = 15;
            label4.Text = "BrandId";
            // 
            // Form1
            // 
            ClientSize = new Size(2490, 1360);
            Controls.Add(label4);
            Controls.Add(textBox4);
            Controls.Add(button3);
            Controls.Add(button1);
            Controls.Add(dgvCoffees);
            Controls.Add(button2);
            Controls.Add(AddButton);
            Controls.Add(textBox3);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(dgvBrands);
            Name = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dgvBrands).EndInit();
            ((System.ComponentModel.ISupportInitialize)dgvCoffees).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }
        private DataGridView dgvCoffees;
        private Button button1;
        private Button button3;
        private TextBox textBox4;
        private Label label4;
    }
}