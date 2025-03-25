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
            dataGridView1.Location = new Point(27, 122);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.Size = new Size(466, 366);
            dataGridView1.TabIndex = 0;
            dataGridView1.CellClick += dataGridView1_CellClick;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15F);
            label1.Location = new Point(999, 183);
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
            label2.Location = new Point(999, 229);
            label2.Name = "label2";
            label2.Size = new Size(178, 28);
            label2.TabIndex = 2;
            label2.Text = "EmployeesNumber";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 15F);
            label3.Location = new Point(999, 275);
            label3.Name = "label3";
            label3.Size = new Size(65, 28);
            label3.TabIndex = 3;
            label3.Text = "CityID";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(1174, 188);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(223, 23);
            textBox1.TabIndex = 5;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(1174, 234);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(223, 23);
            textBox2.TabIndex = 6;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(1174, 280);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(223, 23);
            textBox3.TabIndex = 7;
            // 
            // AddButton
            // 
            AddButton.Font = new Font("Segoe UI", 11F);
            AddButton.Location = new Point(1144, 331);
            AddButton.Name = "AddButton";
            AddButton.Size = new Size(108, 50);
            AddButton.TabIndex = 9;
            AddButton.Text = "Add";
            AddButton.UseVisualStyleBackColor = true;
            AddButton.Click += AddButtonClick;
            // 
            // button2
            // 
            button2.Font = new Font("Segoe UI", 11F);
            button2.Location = new Point(27, 25);
            button2.Name = "button2";
            button2.Size = new Size(108, 50);
            button2.TabIndex = 10;
            button2.Text = "Display data";
            button2.UseVisualStyleBackColor = true;
            button2.Click += DisplayDataButtonClick;
            // 
            // dataGridView2
            // 
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView2.Location = new Point(526, 122);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.Size = new Size(466, 366);
            dataGridView2.TabIndex = 11;
            dataGridView2.CellContentClick += dataGridView2_CellContentClick;
            // 
            // button1
            // 
            button1.Location = new Point(631, 503);
            button1.Name = "button1";
            button1.Size = new Size(94, 48);
            button1.TabIndex = 12;
            button1.Text = "Update";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button3
            // 
            button3.Location = new Point(789, 503);
            button3.Name = "button3";
            button3.Size = new Size(94, 48);
            button3.TabIndex = 13;
            button3.Text = "Delete";
            button3.UseVisualStyleBackColor = true;
            button3.Click += button3_Click;
            // 
            // Form1
            // 
            ClientSize = new Size(1417, 563);
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