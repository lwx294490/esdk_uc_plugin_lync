namespace LyncWpfApp
{
    partial class FrmToolBar
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmToolBar));
            this.pictureBox = new System.Windows.Forms.PictureBox();
            this.btnHsitory = new System.Windows.Forms.Button();
            this.btnSetting = new System.Windows.Forms.Button();
            this.btnDail = new System.Windows.Forms.Button();
            this.btnIP = new System.Windows.Forms.Button();
            this.btnPC = new System.Windows.Forms.Button();
            this.labState = new System.Windows.Forms.Label();
            this.btnFWD = new System.Windows.Forms.Button();
            this.btnMail = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox
            // 
            this.pictureBox.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox.Image")));
            this.pictureBox.Location = new System.Drawing.Point(55, -85);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(250, 202);
            this.pictureBox.TabIndex = 1;
            this.pictureBox.TabStop = false;
            this.pictureBox.Visible = false;
            // 
            // btnHsitory
            // 
            this.btnHsitory.Image = ((System.Drawing.Image)(resources.GetObject("btnHsitory.Image")));
            this.btnHsitory.Location = new System.Drawing.Point(47, 3);
            this.btnHsitory.Name = "btnHsitory";
            this.btnHsitory.Size = new System.Drawing.Size(29, 24);
            this.btnHsitory.TabIndex = 3;
            this.btnHsitory.UseVisualStyleBackColor = true;
            this.btnHsitory.MouseEnter += new System.EventHandler(this.btnHsitory_MouseEnter);
            this.btnHsitory.MouseLeave += new System.EventHandler(this.btnHsitory_MouseLeave);
            // 
            // btnSetting
            // 
            this.btnSetting.Image = ((System.Drawing.Image)(resources.GetObject("btnSetting.Image")));
            this.btnSetting.Location = new System.Drawing.Point(12, 3);
            this.btnSetting.Name = "btnSetting";
            this.btnSetting.Size = new System.Drawing.Size(29, 24);
            this.btnSetting.TabIndex = 6;
            this.btnSetting.UseVisualStyleBackColor = true;
            this.btnSetting.MouseEnter += new System.EventHandler(this.btnSetting_MouseEnter);
            this.btnSetting.MouseLeave += new System.EventHandler(this.btnSetting_MouseLeave);
            // 
            // btnDail
            // 
            this.btnDail.Image = ((System.Drawing.Image)(resources.GetObject("btnDail.Image")));
            this.btnDail.Location = new System.Drawing.Point(82, 3);
            this.btnDail.Name = "btnDail";
            this.btnDail.Size = new System.Drawing.Size(29, 24);
            this.btnDail.TabIndex = 7;
            this.btnDail.UseVisualStyleBackColor = true;
            this.btnDail.MouseEnter += new System.EventHandler(this.btnDail_MouseEnter);
            this.btnDail.MouseLeave += new System.EventHandler(this.btnDail_MouseLeave);
            // 
            // btnIP
            // 
            this.btnIP.Image = ((System.Drawing.Image)(resources.GetObject("btnIP.Image")));
            this.btnIP.Location = new System.Drawing.Point(118, 3);
            this.btnIP.Name = "btnIP";
            this.btnIP.Size = new System.Drawing.Size(29, 24);
            this.btnIP.TabIndex = 8;
            this.btnIP.UseVisualStyleBackColor = true;
            this.btnIP.MouseEnter += new System.EventHandler(this.btnIP_MouseEnter);
            this.btnIP.MouseLeave += new System.EventHandler(this.btnIP_MouseLeave);
            // 
            // btnPC
            // 
            this.btnPC.Image = ((System.Drawing.Image)(resources.GetObject("btnPC.Image")));
            this.btnPC.Location = new System.Drawing.Point(147, 3);
            this.btnPC.Name = "btnPC";
            this.btnPC.Size = new System.Drawing.Size(29, 24);
            this.btnPC.TabIndex = 9;
            this.btnPC.UseVisualStyleBackColor = true;
            this.btnPC.MouseEnter += new System.EventHandler(this.btnPC_MouseEnter);
            this.btnPC.MouseLeave += new System.EventHandler(this.btnPC_MouseLeave);
            // 
            // labState
            // 
            this.labState.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.labState.Location = new System.Drawing.Point(350, 9);
            this.labState.Name = "labState";
            this.labState.Size = new System.Drawing.Size(118, 12);
            this.labState.TabIndex = 2;
            this.labState.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // btnFWD
            // 
            this.btnFWD.Image = ((System.Drawing.Image)(resources.GetObject("btnFWD.Image")));
            this.btnFWD.Location = new System.Drawing.Point(181, 3);
            this.btnFWD.Name = "btnFWD";
            this.btnFWD.Size = new System.Drawing.Size(29, 24);
            this.btnFWD.TabIndex = 10;
            this.btnFWD.UseVisualStyleBackColor = true;
            this.btnFWD.MouseEnter += new System.EventHandler(this.btnFWD_MouseEnter);
            this.btnFWD.MouseLeave += new System.EventHandler(this.btnFWD_MouseLeave);
            // 
            // btnMail
            // 
            this.btnMail.Image = ((System.Drawing.Image)(resources.GetObject("btnMail.Image")));
            this.btnMail.Location = new System.Drawing.Point(217, 3);
            this.btnMail.Name = "btnMail";
            this.btnMail.Size = new System.Drawing.Size(29, 24);
            this.btnMail.TabIndex = 11;
            this.btnMail.UseVisualStyleBackColor = true;
            this.btnMail.MouseEnter += new System.EventHandler(this.btnMail_MouseEnter);
            this.btnMail.MouseLeave += new System.EventHandler(this.btnMail_MouseLeave);
            // 
            // FrmToolBar
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(230)))), ((int)(((byte)(233)))), ((int)(((byte)(239)))));
            this.ClientSize = new System.Drawing.Size(470, 50);
            this.Controls.Add(this.btnMail);
            this.Controls.Add(this.btnFWD);
            this.Controls.Add(this.btnPC);
            this.Controls.Add(this.btnIP);
            this.Controls.Add(this.btnDail);
            this.Controls.Add(this.btnSetting);
            this.Controls.Add(this.btnHsitory);
            this.Controls.Add(this.labState);
            this.Controls.Add(this.pictureBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmToolBar";
            this.Text = "FrmToolBar";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox;
        private System.Windows.Forms.Button btnHsitory;
        private System.Windows.Forms.Button btnSetting;
        private System.Windows.Forms.Button btnDail;
        private System.Windows.Forms.Button btnIP;
        private System.Windows.Forms.Button btnPC;
        private System.Windows.Forms.Label labState;
        private System.Windows.Forms.Button btnFWD;
        private System.Windows.Forms.Button btnMail;

    }
}