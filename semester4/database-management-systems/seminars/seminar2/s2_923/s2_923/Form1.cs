using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.Common;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace s2_923
{
    public partial class Form1: Form
    {

        SqlConnection conn = new SqlConnection("Data Source=DESKTOP-IG95M02;Initial Catalog=sem_2024_2025;" +
            "Integrated Security=True");
        SqlDataAdapter data_adap_spies;
        SqlDataAdapter data_adap_tasks;
        DataSet data_set = new DataSet();
        BindingSource bs_spies = new BindingSource();
        BindingSource bs_tasks = new BindingSource();
        SqlCommandBuilder sqlCommandBuilder;

        public Form1()
        {
            InitializeComponent();
        }

        private void ButtonConnect_Click(object sender, EventArgs e)
        {
            data_adap_spies = new SqlDataAdapter("SELECT * FROM Spies", conn);
            data_adap_tasks = new SqlDataAdapter("SELECT * FROM Tasks", conn);
            sqlCommandBuilder = new SqlCommandBuilder(data_adap_tasks);

            data_adap_spies.Fill(data_set, "Spies");
            data_adap_tasks.Fill(data_set, "Tasks");

            DataRelation rel = new DataRelation("fk_spies_tasks", data_set.Tables["Spies"].Columns["id"],
                data_set.Tables["Tasks"].Columns["spyId"]);

            data_set.Relations.Add(rel);



            bs_spies.DataSource = data_set;
            bs_spies.DataMember = "Spies";

            bs_tasks.DataSource = bs_spies;
            bs_tasks.DataMember = "fk_spies_tasks";

            dataGridViewSpies.DataSource = bs_spies;
            dataGridViewTasks.DataSource = bs_tasks;


            dataGridViewSpies.ReadOnly = true;
            dataGridViewSpies.AllowUserToAddRows = false;
            dataGridViewSpies.AllowUserToDeleteRows = false;


            textBoxTaskDescription.DataBindings.Add("Text", bs_tasks, "taskDesc");

        }

        private void button1_Click(object sender, EventArgs e)
        {
            data_adap_tasks.Update(data_set, "Tasks");
            // handle errors
            // show a message box
        }
    }
}
