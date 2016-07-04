/// <summary>
/// Program to convert Text into Speech, along a talking Dictionary
/// </summary>

using System;
using System.Windows.Forms;
using System.Globalization;
using System.Speech.Synthesis;
using System.Text.RegularExpressions;
using System.Collections.Generic;

namespace TextToSpeech
{
    /// <summary>
    /// This class encloses all methods to form actions of the form
    /// </summary>
    public partial class Form1 : Form
    {
        //Delegate declaration
        delegate void Speech(string x);
        private int _speechRate = 0;        // default values
        private int _speechVolume = 50;     // default values

        /*Form load class*/
        public Form1()
        {
            InitializeComponent();
            label4.Text = _speechRate.ToString(CultureInfo.InvariantCulture);
            label5.Text = _speechVolume.ToString(CultureInfo.InvariantCulture);
            AddInstalledVoicesToList();
        }

        private void BtnSpeakClick(object sender, EventArgs e)
        {
            
        }

        /*change the volume of the application based on user input trackbar values*/
        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            _speechVolume = trackBar2.Value;        // assigning user's preferred value
            label5.Text = _speechVolume.ToString(CultureInfo.InvariantCulture);
        }

        /*change the rate of the application based on user input trackbar values*/
        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            _speechRate = trackBar1.Value;        // assigning user's preferred value
            label4.Text = _speechRate.ToString(CultureInfo.InvariantCulture);
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {   

        }

        /* method to read any passed string of more than one word length */
        private void Sentence(string str)
        {
            using (SpeechSynthesizer synth = new SpeechSynthesizer { Volume = _speechVolume, Rate = _speechRate })
            {
                synth.SelectVoice(comboBox1.Text);
                synth.SetOutputToDefaultAudioDevice();
                synth.Speak(str);
            }
        }

        // method to check validity of word in case of single word
        private void Word(string str)
        {
            try
            {
                int n = int.Parse(str);
                WordGen<int>(n);
            }
            catch (FormatException)
            {
                try
                {
                    char c = char.Parse(str);
                    WordGen<char>(c);
                }
                catch (FormatException)
                {
                    WordGen<string>(str); //in case of valid word create a generic string
                }
            }
        }

        // Generic class
        private void WordGen<T>(T o)
        {
            bool ob = (o.GetType() == typeof(string)); //type checking
            //If type is string, then call the Meaning() method
            if (ob)
            {
                string str = o + "";
                Meaning(str);
            }
            // in case type check fails, i.e., if it is an int or char, read aloud the word
            else
            {
                string str = o + "";
                //If characters were A or I, which have meaning, call Meaning() method
                if (str == "A" || str == "I")
                    Meaning(str);
                using (SpeechSynthesizer synth = new SpeechSynthesizer { Volume = _speechVolume, Rate = _speechRate })
                {
                    synth.SelectVoice(comboBox1.Text);
                    synth.SetOutputToDefaultAudioDevice();
                    synth.Speak(str);
                }
            }
        }

        /* 
        Method to look up meaning of any string having a word
        Checks the first letter of word and open corresponding word list file 
        If word is found, open corresponding meaning list file
        */
        private void Meaning(string str)
        {
            //Reads the word out first
            using (SpeechSynthesizer synth = new SpeechSynthesizer { Volume = _speechVolume, Rate = _speechRate })
            {
                synth.SelectVoice(comboBox1.Text);
                synth.SetOutputToDefaultAudioDevice();
                synth.Speak(str);
            }
            //Add the letter and file path for word files to the dictionary
            Dictionary<string, string> dict = new Dictionary<string, string>(); //hash map creation
            dict.Add("a", "F:\\College\\PROJECTS\\C# and .NET\\Aw.txt");
            dict.Add("b", "F:\\College\\PROJECTS\\C# and .NET\\Bw.txt");
            dict.Add("c", "F:\\College\\PROJECTS\\C# and .NET\\Cw.txt");
            dict.Add("d", "F:\\College\\PROJECTS\\C# and .NET\\Dw.txt");
            dict.Add("e", "F:\\College\\PROJECTS\\C# and .NET\\Ew.txt");
            dict.Add("f", "F:\\College\\PROJECTS\\C# and .NET\\Fw.txt");
            dict.Add("g", "F:\\College\\PROJECTS\\C# and .NET\\Gw.txt");
            dict.Add("h", "F:\\College\\PROJECTS\\C# and .NET\\Hw.txt");
            dict.Add("i", "F:\\College\\PROJECTS\\C# and .NET\\Iw.txt");
            dict.Add("j", "F:\\College\\PROJECTS\\C# and .NET\\Jw.txt");
            dict.Add("k", "F:\\College\\PROJECTS\\C# and .NET\\Kw.txt");
            dict.Add("l", "F:\\College\\PROJECTS\\C# and .NET\\Lw.txt");
            dict.Add("m", "F:\\College\\PROJECTS\\C# and .NET\\Mw.txt");
            dict.Add("n", "F:\\College\\PROJECTS\\C# and .NET\\Nw.txt");
            dict.Add("o", "F:\\College\\PROJECTS\\C# and .NET\\Ow.txt");
            dict.Add("p", "F:\\College\\PROJECTS\\C# and .NET\\Pw.txt");
            dict.Add("q", "F:\\College\\PROJECTS\\C# and .NET\\Qw.txt");
            dict.Add("r", "F:\\College\\PROJECTS\\C# and .NET\\Rw.txt");
            dict.Add("s", "F:\\College\\PROJECTS\\C# and .NET\\Sw.txt");
            dict.Add("t", "F:\\College\\PROJECTS\\C# and .NET\\Tw.txt");
            dict.Add("u", "F:\\College\\PROJECTS\\C# and .NET\\Uw.txt");
            dict.Add("v", "F:\\College\\PROJECTS\\C# and .NET\\Vw.txt");
            dict.Add("w", "F:\\College\\PROJECTS\\C# and .NET\\Ww.txt");
            dict.Add("x", "F:\\College\\PROJECTS\\C# and .NET\\Xw.txt");
            dict.Add("y", "F:\\College\\PROJECTS\\C# and .NET\\Yw.txt");
            dict.Add("z", "F:\\College\\PROJECTS\\C# and .NET\\Zw.txt");
            //Reading first letter of word
            string c = str[0] + "";
            if (dict.ContainsKey(c.ToLower()))
            {
                //Opening corresponding wordlist file based on arraylist/hashmap  
                string fname = dict[c.ToLower()];
                string line;
                int flag = 0;
                int counter = 1;
                System.IO.StreamReader file = new System.IO.StreamReader(fname);
                while ((line = file.ReadLine()) != null)
                {
                    //Looking up the word
                    if (line.ToLower() == str.ToLower())
                    {
                        flag = 1;
                        break;
                    }
                    counter++;
                }
                int counter1 = 1;
                //In case word is found
                if (flag == 1)
                {
                    Dictionary<string, string> mdict = new Dictionary<string, string>();
                    mdict.Add("a", "F:\\College\\PROJECTS\\C# and .NET\\Am.txt");
                    mdict.Add("b", "F:\\College\\PROJECTS\\C# and .NET\\Bm.txt");
                    mdict.Add("c", "F:\\College\\PROJECTS\\C# and .NET\\Cm.txt");
                    mdict.Add("d", "F:\\College\\PROJECTS\\C# and .NET\\Dm.txt");
                    mdict.Add("e", "F:\\College\\PROJECTS\\C# and .NET\\Em.txt");
                    mdict.Add("f", "F:\\College\\PROJECTS\\C# and .NET\\Fm.txt");
                    mdict.Add("g", "F:\\College\\PROJECTS\\C# and .NET\\Gm.txt");
                    mdict.Add("h", "F:\\College\\PROJECTS\\C# and .NET\\Hm.txt");
                    mdict.Add("i", "F:\\College\\PROJECTS\\C# and .NET\\Im.txt");
                    mdict.Add("j", "F:\\College\\PROJECTS\\C# and .NET\\J.txt");
                    mdict.Add("k", "F:\\College\\PROJECTS\\C# and .NET\\Km.txt");
                    mdict.Add("l", "F:\\College\\PROJECTS\\C# and .NET\\Lm.txt");
                    mdict.Add("m", "F:\\College\\PROJECTS\\C# and .NET\\Mm.txt");
                    mdict.Add("n", "F:\\College\\PROJECTS\\C# and .NET\\Nm.txt");
                    mdict.Add("o", "F:\\College\\PROJECTS\\C# and .NET\\Om.txt");
                    mdict.Add("p", "F:\\College\\PROJECTS\\C# and .NET\\Pm.txt");
                    mdict.Add("q", "F:\\College\\PROJECTS\\C# and .NET\\Qm.txt");
                    mdict.Add("r", "F:\\College\\PROJECTS\\C# and .NET\\Rm.txt");
                    mdict.Add("s", "F:\\College\\PROJECTS\\C# and .NET\\Sm.txt");
                    mdict.Add("t", "F:\\College\\PROJECTS\\C# and .NET\\Tm.txt");
                    mdict.Add("u", "F:\\College\\PROJECTS\\C# and .NET\\Um.txt");
                    mdict.Add("v", "F:\\College\\PROJECTS\\C# and .NET\\Vm.txt");
                    mdict.Add("w", "F:\\College\\PROJECTS\\C# and .NET\\Wm.txt");
                    mdict.Add("x", "F:\\College\\PROJECTS\\C# and .NET\\Xm.txt");
                    mdict.Add("y", "F:\\College\\PROJECTS\\C# and .NET\\Ym.txt");
                    mdict.Add("z", "F:\\College\\PROJECTS\\C# and .NET\\Zm.txt");
                    string fname1 = mdict[c.ToLower()];
                    string line1;
                    //Opening corresponding meaning file
                    System.IO.StreamReader file1 = new System.IO.StreamReader(fname1);
                    while ((line1 = file1.ReadLine()) != null)
                    {
                        //When corresponding line is found
                        if (counter == counter1)
                        {
                            string meaning = "Meaning of the word " + str + " is " + line1;
                            //Add the meaning to text in the textbox
                            textBox1.Text = textBox1.Text + " ==>   Meaning : " + line1;
                            //Reads out the meaning
                            using (SpeechSynthesizer synth = new SpeechSynthesizer { Volume = _speechVolume, Rate = _speechRate })
                            {
                                //voice choice
                                synth.SelectVoice(comboBox1.Text);
                                synth.SetOutputToDefaultAudioDevice();
                                synth.Speak(meaning);
                            }
                            break;
                        }
                        counter1++;
                    }
                }
                //Failure of finding word in the file
                else
                {
                    string nomeaning = "Above word was not found in the dictionary. ";
                    using (SpeechSynthesizer synth = new SpeechSynthesizer { Volume = _speechVolume, Rate = _speechRate })
                    {
                        synth.SelectVoice(comboBox1.Text);
                        synth.SetOutputToDefaultAudioDevice();
                        synth.Speak(nomeaning);
                    }
                }
            }
            // invalid input string
            else
            {
                MessageBox.Show("The text you entered began either with a special character or number");
            }
        }

        // Method called uopn 'SPEAK' button click
        private void button1_Click(object sender, EventArgs e)
        {
            // delegate object
            Speech s;
            try
            {
                if (string.IsNullOrEmpty(textBox1.Text))
                {
                    throw (new TextBoxEmpty("Please enter some text in the text box"));
                }
                //Disable group options when word or meaning or both are being read
                groupBox1.Enabled = false;
                String trimText = textBox1.Text.Trim();
                String[] splitText = trimText.Split(' ');
                if (splitText.Length == 1) // single word
                {
                    bool flag = false;
                    //RegularExpressions to check string
                    var regex = new Regex(@"[^a-zA-Z0-9\s]");
                    foreach (char c in textBox1.Text)
                    {
                        string regs = c + "";
                        if (regex.IsMatch(regs))
                        {
                            continue;
                        }
                        else
                        {
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                    {
                        MessageBox.Show("You entered only special characters");
                        return;
                    }
                    s = new Speech(Word);
                }
                else // in case of sentenxw
                {
                    s = new Speech(Sentence);
                }
                //method call - either Word(str) or Sentence(str)
                s(textBox1.Text);
                //Enable group options
                groupBox1.Enabled = true;
            }
            catch (TextBoxEmpty ex)
            {
                // in case of exception
                MessageBox.Show("Text Box is empty: ", ex.Message);
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        /*Adds pre-defined voices to the drop-down list*/
        private void AddInstalledVoicesToList()
        {
            using (SpeechSynthesizer synth = new SpeechSynthesizer())
            {
                foreach(var voice in synth.GetInstalledVoices())
                {
                    comboBox1.Items.Add(voice.VoiceInfo.Name);
                }
            }
            comboBox1.SelectedIndex = 0;
        }

        /*Call the button1_Click function, if user presses 'Enter' key from within the textbox*/
        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            // 13 - character code for 'Enter' key
            if (e.KeyChar == (char)13)
            {
                button1_Click(sender, e);
                e.Handled = true;
            }
        }

        /*Select all text inside textbox when user clicks Ctrl+A*/
        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.A)
            {
                textBox1.SelectAll();
                e.Handled = true;
                e.SuppressKeyPress = true;
            }
        }

        private void label1_MouseHover(object sender, EventArgs e)
        {
            using (SpeechSynthesizer synth = new SpeechSynthesizer { Volume = _speechVolume, Rate = _speechRate })
            {
                synth.SelectVoice(comboBox1.Text);
                synth.SetOutputToDefaultAudioDevice();
                synth.Speak("Click here to enter text");
            }
        }

        private void label1_MouseClick(object sender, MouseEventArgs e)
        {
            textBox1.Focus();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }
    }
}
