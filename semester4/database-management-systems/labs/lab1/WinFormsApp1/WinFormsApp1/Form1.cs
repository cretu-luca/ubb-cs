using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        private DataGridView dgvBrands;
        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private Button AddButton;
        private Button button2;
        private System.ComponentModel.IContainer components = null;

        SqlConnection conn = new SqlConnection("Data Source=np:\\\\.\\pipe\\LOCALDB#A2BB0E06\\tsql\\query;" +
            "Initial Catalog=CoffeeDB;" +
            "Integrated Security=True");

        SqlDataAdapter parent_adapter = new SqlDataAdapter();
        SqlDataAdapter child_adapter = new SqlDataAdapter();
        DataSet parent_dataset = new DataSet();
        DataSet child_dataset = new DataSet();
        int selected;

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
                child_adapter.InsertCommand = new SqlCommand("Insert INTO Coffees (CoffeeName, CoffeeWeight, isAvailable, BrandId)" +
                    "VALUES (@Param1, @Param2, @Param3, @Param4)", conn);

                child_adapter.InsertCommand.Parameters.Add("@Param1", SqlDbType.VarChar).Value = textBox1.Text;
                child_adapter.InsertCommand.Parameters.Add("@Param2", SqlDbType.Int).Value = Int32.Parse(textBox2.Text);
                child_adapter.InsertCommand.Parameters.Add("@Param3", SqlDbType.Int).Value = Int32.Parse(textBox3.Text);
                child_adapter.InsertCommand.Parameters.Add("@Param4", SqlDbType.Int).Value = Int32.Parse(textBox4.Text);

                // child_adapter.InsertCommand.Parameters.Add("@Param3", SqlDbType.VarChar).Value = textBox1.Text;
                // child_adapter.InsertCommand.Parameters.Add("@Param4", SqlDbType.Int).Value = Int32.Parse(textBox3.Text);

                conn.Open();
                child_adapter.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Insert successful.");
                conn.Close();

                child_dataset.Clear();
                child_adapter.Fill(child_dataset);
                dgvCoffees.DataSource = child_dataset.Tables[0]; 
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                conn.Close();
            }
        }

        private void DisplayDataButtonClick(object sender, EventArgs e)
        {
            parent_adapter.SelectCommand = new SqlCommand("Select * FROM Brands", conn);
            parent_dataset.Clear();
            parent_adapter.Fill(parent_dataset);
            dgvBrands.DataSource = parent_dataset.Tables[0];
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dgvCoffees.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            dgvCoffees.MultiSelect = false;
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0 && dgvBrands.Rows[e.RowIndex].Cells["Id"].Value != DBNull.Value)
            {
                selected = Convert.ToInt32(dgvBrands.Rows[e.RowIndex].Cells["Id"].Value);
                LoadChildTable(selected);
            }
        }

        private void LoadChildTable(int selectedId)
        {
            child_adapter = new SqlDataAdapter("SELECT * FROM Coffees WHERE BrandId = @Param", conn);
            child_adapter.SelectCommand.Parameters.AddWithValue("Param", selectedId);

            child_dataset.Clear();
            child_adapter.Fill(child_dataset);
            dgvCoffees.DataSource = child_dataset.Tables[0];
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                SqlCommandBuilder builder = new SqlCommandBuilder(child_adapter);
                child_adapter.Update(child_dataset.Tables[0]);
                LoadChildTable(selected);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (dgvCoffees.SelectedRows.Count > 0)
            {
                int recordId = Convert.ToInt32(dgvCoffees.SelectedRows[0].Cells[0].Value);

                try
                {
                    SqlCommand deleteCommand = new SqlCommand("DELETE FROM Coffees WHERE Id = @id", conn);
                    deleteCommand.Parameters.AddWithValue("id", recordId);

                    conn.Open();
                    deleteCommand.ExecuteNonQuery();
                    conn.Close();

                    LoadChildTable(selected);
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