using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TextToSpeech
{
    public partial class Splash_screen : Form
    {
        private Timer tm;
        public Splash_screen()
        {
            InitializeComponent();
        }

        private void Splash_screen_Load(object sender, EventArgs e)
        {
            tm = new Timer();
            tm.Interval = 5 * 1000; // 5 seconds
            tm.Tick += new EventHandler(tm_Tick);
            tm.Start();
        }

        private void tm_Tick(object sender, EventArgs e)
        {
            tm.Stop();
            Form1 frm = new Form1();
            frm.Show();
            this.Hide();
        }
    }
}
