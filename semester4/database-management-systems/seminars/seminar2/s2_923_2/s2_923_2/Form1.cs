using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace s2_923_2
{
    public partial class Form1: Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void spiesBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.spiesBindingSource.EndEdit();
            this.tableAdapterManager.UpdateAll(this.sem_2024_2025DataSet);

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'sem_2024_2025DataSet.Tasks' table. You can move, or remove it, as needed.
            this.tasksTableAdapter.Fill(this.sem_2024_2025DataSet.Tasks);
            // TODO: This line of code loads data into the 'sem_2024_2025DataSet.Spies' table. You can move, or remove it, as needed.
            this.spiesTableAdapter.Fill(this.sem_2024_2025DataSet.Spies);

        }
    }
}
