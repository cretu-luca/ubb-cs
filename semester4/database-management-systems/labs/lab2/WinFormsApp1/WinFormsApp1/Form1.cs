using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;
using System.Data.Common;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        private System.ComponentModel.IContainer components = null;

        public static string server = ConfigurationManager.AppSettings.Get("server");
        public static string database = ConfigurationManager.AppSettings.Get("database");
        public static string parentTable = ConfigurationManager.AppSettings.Get("parentTable");
        public static string childTable = ConfigurationManager.AppSettings.Get("childTable");
        public static string parentPrimaryKey = ConfigurationManager.AppSettings.Get("parentPrimaryKey");
        public static string childForeignKey = ConfigurationManager.AppSettings.Get("childForeignKey");

        SqlConnection conn = new SqlConnection("Data Source=" + server +
                                               ";Initial Catalog=" + database +
                                               ";Integrated Security=SSPI");

        DataSet dataSet = new DataSet();

        SqlDataAdapter parentDataAdapter = new SqlDataAdapter();
        SqlDataAdapter childDataAdapter = new SqlDataAdapter();

        BindingSource parentBindingSource = new BindingSource();
        BindingSource childBindingSource = new BindingSource();

        SqlCommandBuilder parentCommandBuilder = new SqlCommandBuilder();
        SqlCommandBuilder childCommandBuilder = new SqlCommandBuilder();

        private Dictionary<string, TextBox> childTextBoxes = new Dictionary<string, TextBox>();

        private DataGridView dataGridView1;
        private DataGridView dataGridView2;
        private Button button2;
        private Panel panel1;
        private Button button3;
        private Button button1;

        public Form1()
        {
            InitializeComponent();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void populate()
        {
            parentDataAdapter = new SqlDataAdapter("SELECT * FROM " + parentTable, conn);
            childDataAdapter = new SqlDataAdapter("SELECT * FROM " + childTable, conn);

            SqlCommandBuilder parentBuilder = new SqlCommandBuilder(parentDataAdapter);
            SqlCommandBuilder childBuilder = new SqlCommandBuilder(childDataAdapter);

            parentDataAdapter.Fill(dataSet, parentTable);
            childDataAdapter.Fill(dataSet, childTable);

            DataColumn parentPK = dataSet.Tables[parentTable].Columns[parentPrimaryKey];
            DataColumn childFK = dataSet.Tables[childTable].Columns[childForeignKey];

            DataRelation relation = new DataRelation("FK__Departmen__CityI__74AE54BC", parentPK, childFK);
            dataSet.Relations.Add(relation);

            parentBindingSource.DataSource = dataSet;
            parentBindingSource.DataMember = parentTable;

            childBindingSource.DataSource = parentBindingSource;
            childBindingSource.DataMember = "FK__Departmen__CityI__74AE54BC";

            dataGridView1.DataSource = parentBindingSource;
            dataGridView2.DataSource = childBindingSource;
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                dataGridView2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                dataGridView2.MultiSelect = false;

                conn.Open();
                populate();
                GenerateChildTableTextBoxes();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error in Form1_Load: " + ex.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                parentDataAdapter.Update(dataSet, parentTable);
                childDataAdapter.Update(dataSet, childTable);
                MessageBox.Show("Update with success!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                conn.Close();
            }
        }

        private void InitializeComponent()
        {
            dataGridView1 = new DataGridView();
            dataGridView2 = new DataGridView();
            button1 = new Button();
            button2 = new Button();
            panel1 = new Panel();
            button3 = new Button();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(44, 38);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.Size = new Size(397, 395);
            dataGridView1.TabIndex = 0;
            // 
            // dataGridView2
            // 
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView2.Location = new Point(560, 38);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.Size = new Size(397, 395);
            dataGridView2.TabIndex = 1;
            // 
            // button1
            // 
            button1.Location = new Point(790, 503);
            button1.Name = "button1";
            button1.Size = new Size(167, 61);
            button1.TabIndex = 2;
            button1.Text = "Update";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // button2
            // 
            button2.Location = new Point(560, 503);
            button2.Name = "button2";
            button2.Size = new Size(167, 61);
            button2.TabIndex = 3;
            button2.Text = "Delete";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // panel1
            // 
            panel1.Location = new Point(1074, 38);
            panel1.Name = "panel1";
            panel1.Size = new Size(397, 395);
            panel1.TabIndex = 4;
            // 
            // button3
            //
            button3.Location = new Point(1199, 503);
            button3.Name = "button3";
            button3.Size = new Size(167, 61);
            button3.TabIndex = 5;
            button3.Text = "Add";
            button3.UseVisualStyleBackColor = true;
            button3.Click += new EventHandler(button3_Click);
            // 
            // Form1
            // 
            ClientSize = new Size(1524, 608);
            Controls.Add(button3);
            Controls.Add(panel1);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(dataGridView2);
            Controls.Add(dataGridView1);
            Name = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).EndInit();
            ResumeLayout(false);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count > 0)
            {
                int recordId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells[0].Value);

                try
                {
                    SqlCommand deleteCommand = new SqlCommand($"DELETE FROM {childTable} WHERE {dataGridView2.Columns[0].Name} = @id", conn);
                    deleteCommand.Parameters.AddWithValue("@id", recordId);

                    if (conn.State != ConnectionState.Open)
                    {
                        conn.Open();
                    }

                    deleteCommand.ExecuteNonQuery();
                    conn.Close();

                    childDataAdapter = new SqlDataAdapter($"SELECT * FROM {childTable}", conn);
                    SqlCommandBuilder childBuilder = new SqlCommandBuilder(childDataAdapter);

                    dataSet.Tables[childTable].Clear();
                    childDataAdapter.Fill(dataSet, childTable);

                    MessageBox.Show("Record deleted successfully!");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    if (conn.State == ConnectionState.Open)
                        conn.Close();
                }
            }
            else
            {
                MessageBox.Show("Please select a record to delete");
            }
        }

        private void GenerateChildTableTextBoxes()
        {
            panel1.Controls.Clear();
            childTextBoxes.Clear();

            if (dataSet.Tables.Contains(childTable))
            {
                int yPos = 10;

                foreach (DataColumn column in dataSet.Tables[childTable].Columns)
                {
                    if (column.ColumnName == dataSet.Tables[childTable].Columns[0].ColumnName)
                        continue;

                    Label label = new Label();
                    label.Text = column.ColumnName + ":";
                    label.Location = new System.Drawing.Point(10, yPos);
                    label.Size = new System.Drawing.Size(120, 20);
                    panel1.Controls.Add(label);

                    TextBox textBox = new TextBox();
                    textBox.Name = column.ColumnName;
                    textBox.Location = new System.Drawing.Point(140, yPos);
                    textBox.Size = new System.Drawing.Size(200, 20);
                    panel1.Controls.Add(textBox);

                    childTextBoxes[column.ColumnName] = textBox;

                    yPos += 30;
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                DataRowView parentRow = (DataRowView)parentBindingSource.Current;
                object parentKeyValue = parentRow[parentPrimaryKey];

                DataRow newRow = dataSet.Tables[childTable].NewRow();

                newRow[childForeignKey] = parentKeyValue;

                foreach (var columnName in childTextBoxes.Keys)
                {
                    TextBox textBox = childTextBoxes[columnName];
                    string value = textBox.Text.Trim();

                    if (string.IsNullOrEmpty(value))
                        continue;

                    DataColumn column = dataSet.Tables[childTable].Columns[columnName];

                    try
                    {
                        if (column.DataType == typeof(int))
                            newRow[columnName] = Convert.ToInt32(value);
                        else if (column.DataType == typeof(decimal))
                            newRow[columnName] = Convert.ToDecimal(value);
                        else if (column.DataType == typeof(DateTime))
                            newRow[columnName] = Convert.ToDateTime(value);
                        else
                            newRow[columnName] = value;
                    }
                    catch (FormatException)
                    {
                        MessageBox.Show($"Invalid format for {columnName}. Please enter a valid {column.DataType.Name}.");
                        return;
                    }
                }

                dataSet.Tables[childTable].Rows.Add(newRow);

                childDataAdapter.Update(dataSet, childTable);

                dataSet.Tables[childTable].Clear();
                childDataAdapter.Fill(dataSet, childTable);

                foreach (TextBox textBox in childTextBoxes.Values)
                {
                    textBox.Clear();
                }

                MessageBox.Show("Record added and saved successfully!");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error adding record: " + ex.Message);
            }
        }

        private void button3_Click_1(object sender, EventArgs e)
        {

        }
    }
}