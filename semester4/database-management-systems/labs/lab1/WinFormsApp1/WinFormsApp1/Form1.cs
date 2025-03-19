using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        private DataGridView dataGridView1;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private TextBox textBox4;
        private Button AddButton;
        private Button button2;
        private System.ComponentModel.IContainer components = null;

        SqlConnection conn = new SqlConnection("Data Source=np:\\\\.\\pipe\\LOCALDB#1CA5C300\\tsql\\query;" +
            "Initial Catalog=CityPlanning;" +
            "Integrated Security=True");
        SqlDataAdapter data_adap = new SqlDataAdapter();
        DataSet data_set = new DataSet();

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

        private void AddButtonClick(object sender, EventArgs e)
        {
            try
            {
                data_adap.InsertCommand = new SqlCommand("Insert INTO City (CityName, BudgetID, Population, Surface)" +
                    "VALUES (@CityNameParam, @BudgetIDParam, @PopulationParam, @SurfaceParam)", conn);

                data_adap.InsertCommand.Parameters.Add("@CityNameParam", SqlDbType.VarChar).Value = textBox1.Text;
                data_adap.InsertCommand.Parameters.Add("@BudgetIDParam", SqlDbType.Int).Value = Int32.Parse(textBox2.Text);
                data_adap.InsertCommand.Parameters.Add("@PopulationParam", SqlDbType.Int).Value = Int32.Parse(textBox3.Text);
                data_adap.InsertCommand.Parameters.Add("@SurfaceParam", SqlDbType.Int).Value = Int32.Parse(textBox4.Text);

                conn.Open();
                data_adap.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Insert successful.");
                conn.Close();

                data_set.Clear();
                data_adap.Fill(data_set);
                dataGridView1.DataSource = data_set.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                conn.Close();
            }
        }

        private void DisplayDataButtonClick(object sender, EventArgs e)
        {
            data_adap.SelectCommand = new SqlCommand("Select * FROM City", conn);
            data_set.Clear();
            data_adap.Fill(data_set);
            dataGridView1.DataSource = data_set.Tables[0];
        }
    }
}