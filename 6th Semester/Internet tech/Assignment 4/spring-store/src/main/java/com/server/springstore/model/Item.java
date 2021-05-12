package com.server.springstore.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "item")
public class Item {
    
    @Id
    @Column(name = "aid")
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long aid;  

    @Column(name = "bname")
    private String bname;

    @Column(name = "ctype")
    private String ctype;

    @Column(name = "dsize")
    private String dsize;

    @Column(name = "eprice")
    private int eprice;

    @Column(name = "fdiscount")
    private int fdiscount;

    @Column(name = "gimage")
    private String gimage;

    @Column(name = "latest")
    private String latest;

    public Item() {
        
    }

    public Item(Long aid, String bname, String ctype, String dsize, int eprice, int fdiscount, String gimage, String latest) {
        super();
        this.aid = aid;
        this.bname = bname;
        this.ctype = ctype;
        this.dsize = dsize;
        this.eprice = eprice;
        this.fdiscount = fdiscount;
        this.gimage = gimage;
        this.latest = latest;
    }


    

    public Long getAid() {
        return aid;
    }

    public void setAid(Long aid) {
        this.aid = aid;
    }

    public String getBname() {
        return bname;
    }

    public void setBname(String bname) {
        this.bname = bname;
    }

    public String getCtype() {
        return ctype;
    }

    public void setCtype(String ctype) {
        this.ctype = ctype;
    }

    public String getDsize() {
        return dsize;
    }

    public void setDsize(String dsize) {
        this.dsize = dsize;
    }

    public int getEprice() {
        return eprice;
    }

    public void setEprice(int eprice) {
        this.eprice = eprice;
    }

    public int getFdiscount() {
        return fdiscount;
    }

    public void setFdiscount(int fdiscount) {
        this.fdiscount = fdiscount;
    }

    public String getGimage() {
        return gimage;
    }

    public void setGimage(String gimage) {
        this.gimage = gimage;
    }

    public String getLatest() {
        return latest;
    }

    public void setLatest(String latest) {
        this.latest = latest;
    }
    
}
