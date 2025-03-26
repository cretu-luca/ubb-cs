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
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private Button AddButton;
        private Button button2;
        private System.ComponentModel.IContainer components = null;

        SqlConnection conn = new SqlConnection("Data Source=np:\\\\.\\pipe\\LOCALDB#C859562D\\tsql\\query;" +
            "Initial Catalog=CityPlanning;" +
            "Integrated Security=True");
        SqlDataAdapter city_data_adap = new SqlDataAdapter();
        SqlDataAdapter department_data_adap = new SqlDataAdapter();
        DataSet city_data_set = new DataSet();
        DataSet department_data_set = new DataSet();
        int selectedCityID;

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
                department_data_adap.InsertCommand = new SqlCommand("Insert INTO Department (DepartmentName, EmployeesNumber, CityID)" +
                    "VALUES (@DepartmentNameParam, @EmployeesNumberParam, @CityID)", conn);

                department_data_adap.InsertCommand.Parameters.Add("@DepartmentNameParam", SqlDbType.VarChar).Value = textBox1.Text;
                department_data_adap.InsertCommand.Parameters.Add("@EmployeesNumberParam", SqlDbType.Int).Value = Int32.Parse(textBox2.Text);
                department_data_adap.InsertCommand.Parameters.Add("@CityID", SqlDbType.Int).Value = Int32.Parse(textBox3.Text);

                conn.Open();
                department_data_adap.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Insert successful.");
                conn.Close();

                department_data_set.Clear();
                department_data_adap.Fill(department_data_set);
                dataGridView2.DataSource = department_data_set.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                conn.Close();
            }
        }

        private void DisplayDataButtonClick(object sender, EventArgs e)
        {
            city_data_adap.SelectCommand = new SqlCommand("Select * FROM City", conn);
            city_data_set.Clear();
            city_data_adap.Fill(city_data_set);
            dataGridView1.DataSource = city_data_set.Tables[0];
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dataGridView2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dataGridView2.MultiSelect = false;
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && dataGridView1.Rows[e.RowIndex].Cells["CityID"].Value != DBNull.Value)
            {
                selectedCityID = Convert.ToInt32(dataGridView1.Rows[e.RowIndex].Cells["CityID"].Value);
                LoadDepartment(selectedCityID);
            }
        }

        private void LoadDepartment(int selectedCityID)
        {
            department_data_adap = new SqlDataAdapter("SELECT * FROM Department WHERE CityID = @CityID", conn);
            department_data_adap.SelectCommand.Parameters.AddWithValue("CityID", selectedCityID);

            department_data_set.Clear();
            department_data_adap.Fill(department_data_set);
            dataGridView2.DataSource = department_data_set.Tables[0];
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                SqlCommandBuilder builder = new SqlCommandBuilder(department_data_adap);
                department_data_adap.Update(department_data_set.Tables[0]);
                LoadDepartment(selectedCityID);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (dataGridView2.SelectedRows.Count > 0)
            {
                int recordId = Convert.ToInt32(dataGridView2.SelectedRows[0].Cells[0].Value);

                try
                {
                    SqlCommand deleteCommand = new SqlCommand("DELETE FROM Department WHERE DepartmentID = @id", conn);
                    deleteCommand.Parameters.AddWithValue("id", recordId);

                    conn.Open();
                    deleteCommand.ExecuteNonQuery();
                    conn.Close();

                    LoadDepartment(selectedCityID);
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
                MessageBox.Show("Please select a record to remove");
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}