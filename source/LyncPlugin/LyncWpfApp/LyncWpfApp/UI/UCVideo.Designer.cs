namespace LyncWpfApp
{
    partial class UCVideo
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.remote = new System.Windows.Forms.TextBox();
            this.local = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // remote
            // 
            this.remote.BackColor = System.Drawing.SystemColors.Desktop;
            this.remote.Dock = System.Windows.Forms.DockStyle.Fill;
            this.remote.Enabled = false;
            this.remote.Location = new System.Drawing.Point(0, 0);
            this.remote.Multiline = true;
            this.remote.Name = "remote";
            this.remote.ReadOnly = true;
            this.remote.Size = new System.Drawing.Size(437, 437);
            this.remote.TabIndex = 0;
            // 
            // local
            // 
            this.local.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.local.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.local.Enabled = false;
            this.local.Location = new System.Drawing.Point(0, 327);
            this.local.Margin = new System.Windows.Forms.Padding(0);
            this.local.MaximumSize = new System.Drawing.Size(168, 110);
            this.local.MinimumSize = new System.Drawing.Size(150, 110);
            this.local.Multiline = true;
            this.local.Name = "local";
            this.local.ReadOnly = true;
            this.local.Size = new System.Drawing.Size(150, 110);
            this.local.TabIndex = 1;
            // 
            // UCVideo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.Red;
            this.Controls.Add(this.local);
            this.Controls.Add(this.remote);
            this.Name = "UCVideo";
            this.Size = new System.Drawing.Size(437, 437);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox remote;
        private System.Windows.Forms.TextBox local;
    }
}
