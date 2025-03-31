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

        private DataGridView dataGridView1;
        private DataGridView dataGridView2;
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
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Location = new Point(85, 199);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.Size = new Size(397, 395);
            dataGridView1.TabIndex = 0;
            // 
            // dataGridView2
            // 
            dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView2.Location = new Point(651, 199);
            dataGridView2.Name = "dataGridView2";
            dataGridView2.Size = new Size(397, 395);
            dataGridView2.TabIndex = 1;
            // 
            // button1
            // 
            button1.Location = new Point(753, 704);
            button1.Name = "button1";
            button1.Size = new Size(167, 61);
            button1.TabIndex = 2;
            button1.Text = "button1";
            button1.UseVisualStyleBackColor = true;
            button1.Click += new EventHandler(button1_Click);
            // 
            // Form1
            // 
            ClientSize = new Size(1204, 857);
            Controls.Add(button1);
            Controls.Add(dataGridView2);
            Controls.Add(dataGridView1);
            Name = "Form1";
            Load += new EventHandler(Form1_Load);
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ((System.ComponentModel.ISupportInitialize)dataGridView2).EndInit();
            ResumeLayout(false);

        }
    }
}